#include <iostream>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <unistd.h>
#include <sys/wait.h>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <unordered_map>
#include <fcntl.h>

#include "help.cpp"

#undef BOOST_NO_CXX11_SCOPED_ENUMS
namespace fs = boost::filesystem;

using namespace std;



int main(int argc, char* argv[]){
    bool h = false;
    bool ign = false;
    for (int i = 1; i < argc; i++) {
        if (!h) h = (argv[i] == string("-h"));
        if (!h) h = (argv[i] == string("--help"));
    }
    for (int i = 1; i < argc; i++) {
        if (!ign) ign = (argv[i] == string("-v"));
        if (!ign) ign = (argv[i] == string("--ignore-case"));
        if (!ign) ign = (argv[i] == string("-i"));
        if (!ign) ign = (argv[i] == string("--invert-match"));
    }
    if (h) {
        helping(7);
        return 0;
    }
    else {
        string s;
        if (argc == 1)
            return 0;
        string searched = argv[argc - 1];
        //filename
        if(argc > 2){
            char * pos = strchr(argv[argc-2],'--file=');
            if(pos != NULL){
                string a(argv[argc-2]);
                a.erase(a.begin(), a.begin() + 7);
                int file = open(a.c_str(), O_RDONLY);
                dup2(file, 0);
                close(file);
            }
        }
        while (!cin.fail()) {
            getline(cin, s);
            if(ign){
                //invert match or ignore case
                if (s.find(searched) == string::npos) {
                    cout << s << endl;
                }
            }else{
            if (s.find(searched) != string::npos) {
                cout << s << endl;
            }}
        }

    }}