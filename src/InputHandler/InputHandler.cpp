#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include "InputHandler.h"
#include <sys/stat.h>
#include <experimental/filesystem>
#include "../Utilities/Image.h"


using namespace std;
#define fs experimental::filesystem


string getFileExt(const string& s) {

    size_t i = s.rfind('.', s.length());
    if (i != string::npos) {
        return(s.substr(i+1, s.length() - i));
    }

    return("");
}

bool InputHandler::isValidFileType(const string filepath) {
    return isSupportedFormat(getFileExt(filepath));
}

bool InputHandler::isSupportedFormat(const string &value)
{
    return supportedFormats.find(value) != supportedFormats.end();
}

/// gets pathes of images in folder
/// \param folderPath folder to get files from
/// \param images the found files
/// \return status code

int InputHandler::GetImages(string folderPath, vector<Image> &images){
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(folderPath.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << folderPath << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        string fullPath= folderPath+ "/"+ string(dirp->d_name);
        fs::file_status s= fs::status(fullPath);
        if(!fs::is_directory(s)){ //take only images
           if(isValidFileType(fullPath)){ //take only supported file types
               images.emplace_back(fullPath);
           }
        }
    }
    closedir(dp);
    return 0;


}

