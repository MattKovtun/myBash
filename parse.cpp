#include <iostream>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <unistd.h>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <unordered_map>
#include <sstream>
#include <fcntl.h>

#include "help.h"
//#include "lsboost.h"





#undef BOOST_NO_CXX11_SCOPED_ENUMS
namespace fs = boost::filesystem;
using namespace std;

fs::path DIRECTORY_PATH = fs::current_path();

vector<const char *> create_c(const vector<string> &tokens, const string &name_of_program) {

    vector<const char *> c_args;
    int i = 0;
    c_args.push_back(name_of_program.c_str());
    for (const auto &x : tokens) {
        if (i == 0) {
            i++;
            continue;
        }
        c_args.push_back(x.c_str());
    }
    c_args.push_back(0);
    return c_args;

}

void parse(string b) {
    vector<const char *> c_args;
    istringstream buf(b);
    istream_iterator<string> beg(buf), end;
    vector<string> tokens(beg, end);
    //Перенаправлення виводу (stdout та stderr) запущених процесів

    if(tokens.size() > 2){
        if(tokens[tokens.size() -1] == "2&>1"){
        int file = open(tokens[tokens.size() -2].c_str(), O_TRUNC | O_WRONLY);
        dup2( file, 2);
        dup2(file, 1);
        close(file);
//    freopen(tokens[tokens.size() -3].c_str(),"a",stderr);
//        dup2(fileno(stdout), fileno(stderr));
        tokens.erase(tokens.end()-3, tokens.end());
    }
    else if (tokens[tokens.size() - 2] == ">") {
        int file = open(tokens[tokens.size() - 1].c_str(), O_TRUNC | O_WRONLY);
        dup2(file, 1);
        close(file);
        tokens.erase(tokens.end() - 2, tokens.end());
    }
    else if (tokens[tokens.size() - 2] == "2>") {
        int file = open(tokens[tokens.size() - 1].c_str(), O_TRUNC | O_WRONLY);
        dup2(file, 2);
        close(file);
        tokens.erase(tokens.end() - 2, tokens.end());
    }}

    string func = tokens[0];
    if (func == "mv") {
        if (tokens.size() == 1) cout << "Please enter all arguments or --help to see what to do" << endl;
        else {
            c_args = create_c(tokens, "mv");
        }

    } else if (func == "mkdir") {
        if (tokens.size() == 1) cout << "Please enter all arguments or --help to see what to do" << endl;
        else { c_args = create_c(tokens, "mkdir"); }


    } else if (func == "rm") {
        if (tokens.size() == 1) cout << "Please enter all arguments or --help to see what to do" << endl;
        else { c_args = create_c(tokens, "rm"); }

    } else if (func == "cp") {
        if (tokens.size() == 1) cout << "Please enter all arguments or --help to see what to do" << endl;
        else { c_args = create_c(tokens, "cp"); }

    } else if (func == "ls") {
        c_args = create_c(tokens, "ls");
    } else {
        c_args = create_c(tokens, func);
        execvp(c_args[0], const_cast<char *const *>( c_args.data()));
        perror("Failed to start your command.");
        cout << " But we can help you: " << endl;
        for (int i = 1; i <= 7; i++) { helping(i); }
        return;
    }

    string s = DIRECTORY_PATH.string() + "/" + func;

    const char *path = s.c_str();
    execvp(path, const_cast<char *const *>( c_args.data()));
    perror("Failed to start excec");

}