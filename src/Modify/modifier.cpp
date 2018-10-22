#include "modifier.h"


void Modifier::drawBox(DetectedData data, Mat destination) {
    drawBoxOnSpecificShapes(data.CircleBound, CIRCLE, destination);
    drawBoxOnSpecificShapes(data.RectBound, RECTANGLE, destination);
    drawBoxOnSpecificShapes(data.SquareBound, SQUARE, destination);

}

void Modifier::blurPart(vector<Rect> data, Mat destination){
    for (int i = 0; i < data.size(); ++i) {
        cv::GaussianBlur(destination(data[i]), destination(data[i]), Size(0, 0), 4);
    }
}

void Modifier::drawBoxOnSpecificShapes(vector<Rect> shapes, Scalar color, Mat destination) {
    for(int i = 0; i< shapes.size(); i++){
        rectangle(destination, shapes[i].tl(), shapes[i].br(), color, 2, 8, 0);
    }
}

