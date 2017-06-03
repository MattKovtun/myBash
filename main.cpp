#include <iostream>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <unistd.h>
#include <sys/wait.h>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <unordered_map>
#include <fstream>
#include <fcntl.h>


#include "lsboost.h"
#include "parse.h"

#undef BOOST_NO_CXX11_SCOPED_ENUMS
namespace fs = boost::filesystem;

using namespace std;




vector<string> commands = {"md", "rm", "mv", "cp", "mkdir", "TODO", "ls"};
vector<string> builtin = { "cwd", "cd"};


vector<string> tokenize(string b) {
    istringstream buf(b);
    istream_iterator<string> beg(buf), end;
    vector<string> tokens(beg, end);
    return tokens;
}


void start_builtin_func(string b) {
    istringstream buf(b);
    vector<const char *> c_args;
    istream_iterator<string> beg(buf), end;
    vector<string> tokens(beg, end);
    string func = tokens[0];
    if (func == "cd") {
        if (tokens.size() != 1) {
            cd(tokens[1]);
        } else { cout << "Please enter directory... " << endl; }
        return;}
     else if (func == "cwd") {
        pwd(b);
        return;
    }
}


int start_process(string command) {
    istringstream buf(command);
    istream_iterator<string> beg(buf), end;
    vector<string> vector_commands = tokenize(command);
    if (find(builtin.begin(), builtin.end(), vector_commands[0]) != builtin.end()) {
        start_builtin_func(command);
        return 1;
    }
    long index = command.find("#");
    if(index != -1) {
        string sub_str2 = command.substr (0, index);
        command = sub_str2;}


        pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        istringstream buf(command);
        vector<const char *> c_args;
        istream_iterator<string> beg(buf), end;
        vector<string> tokens(beg, end);

        parse(command);

        _exit(EXIT_SUCCESS);
    } else {
        int status;
        (void) waitpid(pid, &status, 0);
    }
    return EXIT_SUCCESS;
}


int main(int argc, char *argv[]) {
    parse:DIRECTORY_PATH = (fs::current_path());
    if (argc == 2) {
        ifstream file(argv[1]);
        string str;
        while (getline(file, str)) {
            cout << "~ " << str << endl;
            start_process(str);
        }
        return 0;
    }

    bool quit = false;
    cout
            << "Welcome to my shell! Type : \"mkdir -h\" for example, to see help!\nType \"TODO\" to see problems to be solved."
            << endl;

    while (!quit) {
        string command;
        cout << "~ ";

        getline(cin, command);
        string tmp = command;

        tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
        if (tmp.empty())continue;
        vector<string> vector_commands = tokenize(command);
        if (vector_commands[0] == "exit" && vector_commands.size() >= 2) {
            int status;
            if(vector_commands[1][0] == '#'){ status = 0;}
            else{ status = stoi(vector_commands[1]);}
            return status;
        } else if (vector_commands[0] == "exit")
            return 0;

        start_process(command);
    }

}
