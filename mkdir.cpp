//
// Created by matt on 3/20/17.
//

////////////////////////////////////////////////////////////
/////////////////DONE///////////////DONE////////////////////
////////////////////////////////////////////////////////////


#include <sstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include "help.cpp"

namespace fs = boost::filesystem;
using namespace std;

int main(int argc, char *argv[]) { // Done
    bool h = false;
    for (int i = 1; i < argc; i++) {
        if (!h) h = (argv[i] == string("-h") ? true : false);
        if (!h) h = (argv[i] == string("--help") ? true : false);
    }
    if (h) {
        helping(2);
        return 0;
    }

    string dir_name = argv[1];
    fs::path dir(dir_name);
    if (fs::create_directory(dir)) {
        cout << "Success" << endl;
    } else {

        cout << "Directory already exists" << endl;
    }


}
