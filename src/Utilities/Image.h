#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Image {

private:
    string fullPath;
    string fileName;
    Mat imageMat;
    bool isLoaded;

    /// Extracts the file name from the full path and sets the property.
    void setFileName();

public:
    Image(string path);

    /// @return full path of the image.
    string getPath();

    /// @return The image file name.
    string getFileName();

    /// @return Mat of the image, if loaded.
    Mat getImageMat();

    /// Loads an image inside the relevant property.
    void loadImageMat();

    /// @return true if the picture has been loaded.
    bool hasBeenLoaded();

    /// Free the memory taken by the Mat property.
    void freeMatMemory();


};


