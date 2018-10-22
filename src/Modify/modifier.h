#pragma once

#include "../types.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Modifier{
public:
    /// Draw box around different sets of shapes from the data on the destination picture.
    /// Each shape type with different color, according to it's set.
    /// \param data The shapes data organized by shape type.
    /// \param destination The picture to draw on.
    void drawBox(DetectedData data, Mat destination);
    void blurPart(vector<Rect> data, Mat destination);

private:
    //colors are in BRG
    Scalar CIRCLE = Scalar(255, 0, 0); // Blue
    Scalar SQUARE = Scalar(0, 0, 255); // Red
    Scalar RECTANGLE = Scalar(0, 255, 0); // Green

    /// Draw box around a single set of shapes.
    /// \param shapes a single set of shapes to box.
    /// \param color the color of the frame
    /// \param destination the picture to draw on.
    void drawBoxOnSpecificShapes(vector<Rect> shapes, Scalar color,  Mat destination);
};


