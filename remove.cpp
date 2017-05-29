//
// Created by natasha on 4/1/17.
//

////////////////////////////////////////////////////////////
/////////////////DONE///////////////DONE////////////////////
////////////////////////////////////////////////////////////
#include <iostream>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <unistd.h>
#include <sys/wait.h>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <unordered_map>
#include "help.cpp"

#undef BOOST_NO_CXX11_SCOPED_ENUMS
namespace fs = boost::filesystem;
using namespace std;


bool asking() {
    char type;
    while (!cin.fail() && type != 'y' && type != 'n') {
        cout << " <-- Do you want to delete these files? y/n " << endl;
        cin >> type;
    }

    return type == 'y' ? true : false;
}

int main(int argc, char *argv[]) { // Done
    vector<string> to_delete;
    bool answerF = false;
    bool answerR = false;

    bool h = false;
    for (int i = 1; i < argc; i++) {
        if (!h) h = (argv[i] == string("-h") ? true : false);
        if (!h) h = (argv[i] == string("--help") ? true : false);
    }
    if (h) {
        helping(1);
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        if (!answerF)answerF = (argv[i] == string("-f") ? true : false);
        if (!answerR)answerR = (argv[i] == string("-R") ? true : false);
        if (argv[i] != string("-f") && argv[i] != string("-R"))to_delete.push_back(string(argv[i]));
    }

//    if (!answerF) answerF = asking();
//    if (!answerF) return 0;
    for (int i = 0; i < to_delete.size(); ++i) {
        if (!answerR && fs::is_directory(to_delete[i])) {
            cout << "You can't remove directory --> " << to_delete[i] << endl;
        } else if (fs::remove_all(to_delete[i])) {
            if (!answerF) answerF = asking();
            if (!answerF) return 0;
            cout << "Success" << endl;
        } else {
            cout << "Directory not found" << endl;
        }
    }
}




