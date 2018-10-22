#ifndef STUDENTPROJECT_DETECTION_H
#define STUDENTPROJECT_DETECTION_H


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "../types.h"
#include "../Utilities/Image.h"


using namespace cv;
using namespace std;

enum ShapeTypes{
    circle,
    rectangle,
    square,
    notRelevant = -1
};

class Detector{
    Mat src_gray;
    Mat src;
    vector<Rect> * DetectedShapesRects;
public:
    DetectedData Detect(Image& img);
    Detector();
    ~Detector();
private:
    void LoadImgAndGrayscale(Image &original);
    vector<vector<Point> > GetContoursOfPolygons();
    void SetBoundsForPolygons(vector<vector<Point> > contours);
    void SetBoundsForCircles();
    void ClearDetectedRects();
    void groupRects();
};

#endif //STUDENTPROJECT_DETECTION_H

