//
// Created by matt on 3/20/17.
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


bool asking_cp() {
    char type;
    while (!cin.fail() && type != 'y' && type != 'n') {
        cout << " <-- Do you want to copy these files? y/n " << endl;
        cin >> type;
    }
    return type == 'y';
}

void cp_copy(string s, fs::path destination_path) {
    fs::path source_path(s);
    if (!fs::exists(source_path))return;
    if (fs::is_directory(destination_path)){
        destination_path /= source_path.filename();}
    try {
        fs::copy_file(source_path, destination_path, fs::copy_option::overwrite_if_exists);
        cout << "Success" << endl;
    }
    catch (...) {
        cout << "No such file " << s << endl;
    }

}

int main(int argc, const char *argv[]) {
    vector<string> to_cp;

    bool h = false;
    for (int i = 1; i < argc; i++) {
        if (!h) h = (argv[i] == string("-h"));
        if (!h) h = (argv[i] == string("--help"));
    }
    if (h) {
        helping(4);
        return 0;
    }
    bool answerF = false;
    for (int i = 1; i < argc; i++) {
        if (!answerF) answerF = (argv[i] == string("-f"));
        if (argv[i] != string("-f"))to_cp.push_back(string(argv[i]));
    }

    fs::path destination_path(argv[argc - 1]);
    if(to_cp.size() > 2){
    for (int i = 0; i < to_cp.size() -1; ++i) {
        bool ask = answerF;
        if(!ask){
        if (fs::exists(destination_path.string() + "/" + to_cp[i])){
            ask = asking_cp();
        }else{
            ask = true;
        } }
        if (ask)cp_copy(to_cp[i], destination_path);

    }}
    else {
        bool ask = answerF;
        if(!ask){
            if (fs::exists(destination_path)){
                ask = asking_cp();
            } else{
                ask = true;
            }}
        if (ask)cp_copy(to_cp[0], to_cp[1]);
    }
}
