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
#include "help.cpp"

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



void my_copy(string s, fs::path destination_path) {
    fs::path source_path(s);
    if (!fs::exists(source_path))return;
    if (fs::is_directory(destination_path)){
        destination_path /= source_path.filename();}
    try {
        fs::rename(s, destination_path);
        cout << "Success" << endl;
    }
    catch (...) {
        cout << "No such file " << s << endl;
    }

}

int main(int argc, const char *argv[]) {

    vector<string> to_mv;

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
    for (int i = 1; i < argc; i++) {
        if (!answerF) answerF = (argv[i] == string("-f"));
        if (argv[i] != string("-f"))to_mv.push_back(string(argv[i]));
    }

    fs::path destination_path(argv[argc - 1]);
    if(to_mv.size() > 2){
        for (int i = 0; i < to_mv.size() -1; ++i) {
            bool ask = answerF;
            if(!ask){
                if (fs::exists(destination_path.string() + "/" + to_mv[i])){
                    ask = asking_rename();
                }else{
                    ask = true;
                } }
            if (ask)my_copy(to_mv[i], destination_path);

        }}
    else {
        bool ask = answerF;
        if(!ask){
            if (fs::exists(destination_path)){
                ask = asking_rename();
            } else{
                ask = true;
            }}
        if (ask)my_copy(to_mv[0], to_mv[1]);
    }
}

