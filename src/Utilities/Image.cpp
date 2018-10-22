
#include "Image.h"

Image::Image(string path) {
    fullPath = path;
    isLoaded = false;
    setFileName();
}

void Image::setFileName() {
    string result(basename((char*)(fullPath.c_str())));
    fileName = result;
}

string Image::getFileName() {
    return fileName;
}

void Image::loadImageMat() {
    if(!isLoaded){
        imageMat = imread(fullPath);
        isLoaded = true;
    }
}

Mat Image::getImageMat() {
    if(isLoaded){
        return imageMat;
    }
    throw ios_base::failure("Picture is not loaded");
}

string Image::getPath() {
    return fullPath;
}

bool Image::hasBeenLoaded() {
    return isLoaded;
}

void Image::freeMatMemory() {
    imageMat.release();
    isLoaded = false;
}
