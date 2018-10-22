#include <cstdio>
#include "Detection/detection.h"
#include "Modify/modifier.h"
#include "Output/Output.h"
#include "InputHandler/InputHandler.h"
#include "Utilities/Image.h"


using namespace std;

int main (int argc, char *argv[]) {
    char* inputDir = argv[1];
    char* outputDir = argv[2];
    Modifier modifier;
    Detector detector;
    InputHandler inputHandler;
    DetectedData detectedData;
    string fileName;
    Mat sourceImage;
    vector<Image> images;
    inputHandler.GetImages(inputDir, images); // get's the paths of the pics inside the folder
    Output output(outputDir); // starting the output process - Makes folder + text file
    for(int j = 0; j < images.size(); j++)
    {
        //todo change method calls (after the full refactoring of output and draw
        fileName = output.getFileNameFromPath(images[j].getPath()); // extracting file name from path.
        detectedData = detector.Detect(images[j]);
        sourceImage = images[j].getImageMat();
        modifier.blurPart(detectedData.RectBound, sourceImage);
        //modifier.drawBox(detectedData, sourceImage);
        output.savePicture(sourceImage, fileName);
        output.sumFileActions(fileName, detectedData);
        images[j].freeMatMemory();
    }
    cout << "Done! see result at " << output.getFullPath();
} 