//
// Created by matt on 3/23/17.
//



#include <algorithm> // ????
#include <sstream> // ????


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


    string func = tokens[0];
//    cout << func << endl;
    if (func == "TODO") {
        TODO();
        return;
    }
    else if (func == "pwd"){
        pwd(b);
        return;
    }
    else if (func == "mv") {
        c_args = create_c(tokens, "./mv");

    } else if (func == "mkdir") {
        c_args = create_c(tokens, "./mkdir");


    } else if (func == "rm") {
        c_args = create_c(tokens, "./rm");

    } else if (func == "cp") {
        c_args = create_c(tokens, "./cp");

    } else if (func == "cd") {
        cd(tokens[1]);
    } else if (func == "ls") {
        c_args = create_c(tokens, "name");
        ls(c_args.size(), c_args.data());
        return;
    } else {
        c_args = create_c(tokens, func);

    }

    execvp(c_args[0], const_cast<char *const *>( c_args.data()));
    perror("Failed to start excec");

}

