//
// Created by matt on 3/20/17.
//

////////////////////////////////////////////////////////////
/////////////////DONE///////////////DONE////////////////////
////////////////////////////////////////////////////////////


#include <sstream>

int mkdir(int argc, const char *argv[]) { // Done
    // mkdir /home/matt/CLionProjects/myBash/new


    string dir_name = argv[1];
    fs::path dir(dir_name);
    if (fs::create_directory(dir)) {
        cout << "Success" << endl;
    } else {
        cout << "Directory already exists" << endl;
    }

}
