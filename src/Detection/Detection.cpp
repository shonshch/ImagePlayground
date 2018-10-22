#include "detection.h"



using namespace std;
using namespace cv;

int shapeTypesCount=3;
int numOfContoursInQuadrate= 4;



/// calculates the distance between 2 points
/// \param p first point
/// \param q second point
/// \return the dist
double distSq(Point p, Point q)
{
    double distancex = p.x - q.x;
    distancex *= (p.x - q.x);
    double distancey = p.y - q.y;
    distancey *= (p.y - q.y);

    return sqrt(distancex + distancey);
}

// This function returns true if (p1, p2, p3, p4) form a
// square, otherwise false
bool isSquare(Point p1, Point p2, Point p3, Point p4)
{
    double d2 = distSq(p1, p2);  // from p1 to p2
    double d3 = distSq(p2, p3);  // from p1 to p3
    double d4 = distSq(p3, p4);  // from p1 to p4

    return ((d2==d3) && (d3==d4));

}

///groups sub-rectangles to avoid duplicates
void Detector::groupRects()
{
    for (int j = 0; j < shapeTypesCount; ++j) {
        auto origin = DetectedShapesRects[j];
        int size = DetectedShapesRects[j].size();
        for( int i = 0; i < size; i++ )
        {
            DetectedShapesRects[j].push_back(Rect(origin[i]));
        }
        groupRectangles(DetectedShapesRects[j], 1, 0.2);
    }

}

Detector::Detector() {
    DetectedShapesRects = new vector<Rect>[shapeTypesCount];//three types of shapes
    //0-circle; 1-rectangle; 2-square

}

/// returns rectangles that bound the detected shapes
/// \param imgPath path of the image
/// \return DetectedData object,with the rectangles
DetectedData Detector::Detect(Image &img){
    ClearDetectedRects();
    if(!img.getPath().empty()){
        LoadImgAndGrayscale(img);
        if (img.getImageMat().data && src_gray.data) {
            SetBoundsForPolygons(GetContoursOfPolygons());
            SetBoundsForCircles();
            groupRects();

            return DetectedData{DetectedShapesRects[0], DetectedShapesRects[1], DetectedShapesRects[2]};
        }
    }
    return DetectedData{{},{},{}};
}

void Detector::ClearDetectedRects(){

    for (int i = 0; i < shapeTypesCount; ++i) {
        DetectedShapesRects[i].erase(DetectedShapesRects[i].begin(), DetectedShapesRects[i].end());
    }

}

///detect circles and calculates bounding rectangles over them
void Detector::SetBoundsForCircles(){
    vector<Vec3f> circles;
    vector<Rect> circBounds;
    float radius;
    HoughCircles(src_gray, circles, HOUGH_GRADIENT, 1, 40,
                 100, 30, 3, 90);
    for( size_t i = 0; i < circles.size(); i++ )
    {
        radius= circles[i][2];
        Rect newBound(circles[i][0]-radius,circles[i][1]-radius,2*radius,2*radius );
        DetectedShapesRects[ShapeTypes ::circle].push_back(newBound);
    }
}

/// finds the outlines of objects in image
/// \return points of contours
vector<vector<Point> > Detector::GetContoursOfPolygons(){
    Mat threshold_output1;
    Mat threshold_output2;

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    /// Detect edges using Threshold
    adaptiveThreshold(src_gray, threshold_output1, 300, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 11, 12);
    blur( threshold_output1, threshold_output1, Size(3,3) );
    medianBlur ( threshold_output1, threshold_output1, 3 );
    erode( threshold_output1, threshold_output2, Mat() );

    /// Find contours
    findContours( threshold_output2, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    return contours;
}
/// set the bounding rectangles for detected polygons
/// \param contours contours of polygons
void Detector::SetBoundsForPolygons(vector<vector<Point> > contours){
    vector<vector<Point> > contours_poly( contours.size() );

    int shapetype;
    for( int i = 0; i < contours.size(); i++ )
    {
        double epsilon = 0.04*arcLength(contours[i], true);
        approxPolyDP( Mat(contours[i]), contours_poly[i], epsilon, true );
        if(contours_poly[i].size()==numOfContoursInQuadrate){
            if (isSquare(contours_poly[i][0],contours_poly[i][1],
                         contours_poly[i][2], contours_poly[i][3])){ //square
                shapetype= ShapeTypes ::square;
            }
            else{
                shapetype=ShapeTypes ::rectangle;
            }
        }

        else {
            shapetype = ShapeTypes ::notRelevant;
        }
        if (shapetype!=ShapeTypes ::notRelevant){
            DetectedShapesRects[shapetype].push_back(boundingRect( Mat(contours_poly[i]) ));

        }

    }
}

/// loads an image and convert it to gray
/// \param imgPath image to load
void Detector::LoadImgAndGrayscale(Image &original){
    original.loadImageMat();

    if(original.getImageMat().data) {
        // Convert image to gray
        cvtColor(original.getImageMat(), src_gray, CV_BGR2GRAY);
    }
}
Detector::~Detector() {
    // deletes mats
    //src.release();
    src_gray.release();

    //deletes rectangles vector
    ClearDetectedRects();
    delete [] DetectedShapesRects;

}