#ifndef STUDENTPROJECT_TYPES_H
#define STUDENTPROJECT_TYPES_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;



struct DetectedData{
    vector<Rect> CircleBound;
    vector<Rect> RectBound;
    vector<Rect> SquareBound;
};
#endif //STUDENTPROJECT_TYPES_H
