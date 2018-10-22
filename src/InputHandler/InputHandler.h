#ifndef STUDENTPROJECT_INPUTHANDLER_H
#define STUDENTPROJECT_INPUTHANDLER_H

#include <iostream>
#include <vector>
#include <set>
#include "../Utilities/Image.h"

using namespace std;


class InputHandler{
    set<string> supportedFormats {"bmp", "pbm","pgm", "ppm", "jpeg", "jpg", "jpe", "jp2", "png"};


public:
    int GetImages(string folderPath, vector<Image> &images);

private:
    bool isValidFileType(string path);
    bool isSupportedFormat(const string &value);
};
#endif //STUDENTPROJECT_INPUTHANDLER_H
