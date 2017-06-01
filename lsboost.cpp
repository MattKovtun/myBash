//
// Created by matt on 3/20/17.
//
#include <iostream>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <unistd.h>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>


#undef BOOST_NO_CXX11_SCOPED_ENUMS
namespace fs = boost::filesystem;

using namespace std;

int cd(string new_dir) {
    if (new_dir.find("-h") != std::string::npos || new_dir.find("--help") != std::string::npos) {
        cout << "cd <path>  -- перейти до шляху <path>" << endl;
    } else {
        int status;
        if (new_dir == ".") {
            status = chdir("..");
        } else {
            status = chdir(new_dir.c_str());
        }
        if (status == -1) {
            cout << "no such directory" << endl;
            return -1;
        }
        return chdir(new_dir.c_str());

    }
}

fs::path pwd(string line) { // Done
    if (line.find("-h") != std::string::npos || line.find("--help") != std::string::npos) {
        cout << "cwd - вивести поточний шлях " << endl;
        return fs::path();
    } else {
        fs::path full_path(fs::current_path());
        cout << full_path << endl;
        return full_path;
    }
}





