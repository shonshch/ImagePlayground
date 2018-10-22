#pragma  once

#include <opencv2/opencv.hpp>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include "../types.h"
#include <libgen.h>

using namespace std;
using namespace cv;


class Output {

public:
    /// Extracts the file name and extention from a full path
    /// \param path the full path of the file
    /// \return the name of the path
    string getFileNameFromPath(string path);
private:
    string fullPath;
    string removeCommand;


    /// Adds line to the text file.
    /// \param text the content of the line
    /// \param closeLine true if should make a new line after writing, otherwise false.
    void addLineToTextFile(string text, bool closeLine);

    /// Writes to the file the number of shapes detected in the shapeVector
    /// \param shapeVector the detected shape data.
    void addNumOfShapesToTextFile(vector<Rect> shapeVector);

public:
    /// Saves a copy of the manipulated picture in the parent directory
    /// \param picture the picture to save
    /// \param fileName name for the file. has to include extention.
    void savePicture(Mat picture, string fileName);

    /// Adds to a sum of the current picture data to the text file.
    /// \param fileName the name of the file detected.
    /// \param data the data detected in that file.
    void sumFileActions(string fileName, DetectedData data);

private:
    /// Makes the working directory, if exists cleans it.
    void makeFolder(char* folderPath);

    /// Makes a text file named Summery.txt at the working directory
    void makeSummeryFile();

    /// Setting up the full working directory path for future use.
    /// folderPath the path of the working directory parent
    void setupPath(char* folderPath);

    /// Setting up the remove command syntax for future use
    void setupRemoveCommand();

public:
    explicit Output(char* folderPath);
    string getFullPath();


};



