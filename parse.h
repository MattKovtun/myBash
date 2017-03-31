//
// Created by matt on 3/23/17.
//

#ifndef MYBASH_PARSE_H
#define MYBASH_PARSE_H

#endif //MYBASH_PARSE_H


#include <algorithm> // ????
#include <sstream> // ????

vector<const char *> create_c(vector<string> tokens, string name_of_program){
    vector<const char *> c_args;
    int i = 0;
    c_args.push_back(name_of_program.c_str());
    for (const auto &x : tokens) {
        if (i == 0){
            i++;
            continue;
        }
        c_args.push_back(x.c_str());
    }
    c_args.push_back(0);
    return c_args;

}

int parse(string b) {
    vector<const char *> c_args;
    istringstream buf(b);
    istream_iterator<string> beg(buf), end;
    vector<string> tokens(beg, end);
    bool flags[5];
    for (auto &s: tokens) {
        //if(s == "-h"){return helping()};
        if (s == "-l") { flags[0] = 1; }
        if (s == "--sort=S" || s == "--sort=t" || s == "--sort=X") { flags[1] = 1; }
        if (s == "-r") { flags[2] = 1; }
        if (s == "-f") { flags[3] = 1; } // мовчки перезаписувати
        if (s == "-R") { flags[4] = 1; } //видаляти директорії
    }
    string func = tokens[0];



    if (func == "cwd")cwd();
    if (func == "cd") { string path = tokens[1]; }
    if (func == "mv") {
        c_args = create_c(tokens, "name");
        move(c_args.size(), c_args.data());
    }
    if (func == "mkdir") {
        c_args = create_c(tokens, "name");
        mkdir(c_args.size(), c_args.data());     //execvp( c_args[0], const_cast<char* const*>( c_args.data() ) );
    }
    if (func == "ls") {
        string path;
        for (auto &s: tokens) {
            if (s != func && s[0] != '-') {
                path = s;
            }
        }
        ls_boost();
    }
};
