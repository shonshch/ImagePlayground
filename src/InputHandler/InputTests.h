

#include "InputHandler.h"

void tryGetInput();

void tryGetInput(char* path){
    std::string dir(path);
    vector<string> files = vector<string>();
    InputHandler h;

    h.GetImages(dir, files);

    for (unsigned int i = 0;i < files.size();i++) {
        cout << files[i] << endl;
    }
}