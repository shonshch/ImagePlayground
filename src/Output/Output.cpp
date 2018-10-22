#include "Output.h"


using namespace std;

const string FILE_NAME = "/Summery.txt";
const string FOLDER_NAME = "/ProgramOutput";

Output::Output(char* folderPath) {
    setupPath(folderPath);
    setupRemoveCommand();
    makeFolder(folderPath);
    makeSummeryFile();
}

void Output::makeFolder(char* folderPath) {
    struct stat st;
    if(stat(folderPath,&st) == 0) {
        const int dir_err = mkdir(this->fullPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (-1 == dir_err) {
            system(this->removeCommand.c_str());
        }
    }
    else{
            throw ios_base::failure("No such directory");
        }
}

void Output::setupPath(char* folderPath) {
    string path(folderPath);
    string folderName = path + FOLDER_NAME;
    this->fullPath = folderName;
}

void Output::setupRemoveCommand() {
    string command = "exec rm -r ";
    string path(this->fullPath);
    command = command + path + "/*";
    this->removeCommand = command;
}

void Output::makeSummeryFile() {
    string path = fullPath + FILE_NAME;
    ofstream resultFile (path.c_str());
    resultFile << "Summery" << endl;
    resultFile.close();
}

void Output::savePicture(Mat picture, string fileName) {
    imwrite(fullPath + "/" +  fileName, picture);
}

void Output::addLineToTextFile(string text, bool closeLine) {
    string path = fullPath + FILE_NAME;
    ofstream resultFile (path.c_str(), std::ios_base::app);
    resultFile << text;
    if (closeLine){
        resultFile << endl;
    }
    resultFile.close();
}

void Output::addNumOfShapesToTextFile(vector<Rect> shapeVector) {
    string numOfShapes;
    stringstream streamer;
    streamer << shapeVector.size();
    streamer >> numOfShapes;
    addLineToTextFile(" " + numOfShapes, true);
}

void Output::sumFileActions(string fileName, DetectedData data) {
    addLineToTextFile("----------------", true);
    addLineToTextFile("Picture name: " + fileName, true);
    addLineToTextFile("\tRecs:", false);
    addNumOfShapesToTextFile(data.RectBound);
    addLineToTextFile("\tCircles:", false);
    addNumOfShapesToTextFile(data.CircleBound);
    addLineToTextFile("\tSquares:", false);
    addNumOfShapesToTextFile(data.SquareBound);
}

string Output::getFileNameFromPath(string path) {
    string result(basename((char*)(path.c_str())));
    return result;

}

string Output::getFullPath() {
    return fullPath;
}


