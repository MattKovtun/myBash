//
// Created by natasha on 3/20/17.
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
#include "help.h"

#undef BOOST_NO_CXX11_SCOPED_ENUMS
namespace fs = boost::filesystem;
using namespace std;


bool asking_rename() {
    char type;
    while (!cin.fail() && type != 'y' && type != 'n') {
        cout << " <-- Do you want to rename these files? y/n " << endl;
        cin >> type;
    }
    return type == 'y';
}

void my_copy(string s, fs::path dest, bool ask) {
    fs::path src(s);
    if (fs::is_directory(dest))dest /= src.filename();
    ask = (ask == false ? asking_rename() : true);
    if (ask) {
        try {
            fs::rename(src, dest);
            cout << "Success" << endl;
        }
        catch (...) {
            cout << "No such file " << s << endl;
        }
    }
}


int main(int argc, const char *argv[]) {
    vector<string> to_rename_move;

    bool h = false;
    for (int i = 1; i < argc; i++) {
        if (!h) h = (argv[i] == string("-h"));
        if (!h) h = (argv[i] == string("--help"));
    }
    if (h) {
        helping(3);
        return 0;
    }

    bool answerF = false;
    for (int i = 1; i < argc - 1; i++) {
        if (!answerF)answerF = (argv[i] == string("-f"));
        if (argv[i] != string("-f"))to_rename_move.push_back(string(argv[i]));
    }
    fs::path dest(argv[argc - 1]);
    for (int i = 0; i < to_rename_move.size(); ++i) {
        my_copy(to_rename_move[i], dest, answerF);

    }
}

