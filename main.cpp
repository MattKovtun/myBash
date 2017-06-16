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
vector<string> builtin = {"cwd", "cd"};


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
        return;
    } else if (func == "cwd") {
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



    //коментарі
    long index = command.find("#");
    if (index != -1) {
        string sub_str2 = command.substr(0, index);
        command = sub_str2;
    }
    //коментарі ^

    //змінні середовища
    //працює тільки в форматі export VAR=ABCC
    if (command.find("export") != -1) {
        size_t found = command.find("=");
        command.replace(0, 7, "");
        if (found != -1) {
            string namVar = command.substr(0, found - 7);
            string var = command.substr(found - 6, command.length());
            setenv(namVar.c_str(), var.c_str(), true);
            // cout << namVar << ", " << var << endl;
        }
        return 1;
    }
    //змінні ^


    // конвеєр
    vector<string> strings;
    istringstream f(command);
    string s;
    vector<string> cmd;


    while (getline(f, s, '|')) {
        strings.push_back(s);
        cmd.push_back(s);
//        cout << s << endl;
    }
    int pipes[cmd.size()][2];
    if (cmd.size() >= 2) {
        pid_t pids[cmd.size()];
        for (int i = 0; i < cmd.size(); ++i) {

            pids[i] = fork();
            if (pids[i] == -1) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
            int pipefd[2];
            pipe(pipefd);
            pipes[i][0] = pipefd[0];
            pipes[i][1] = pipefd[1];
        }


//        pid_t pid = fork();
        for (int i = 0; i < cmd.size() - 1; ++i) {
            if (pids[i] == -1) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }

            if (pids[i] == 0) {

                close(pipes[i + 1][0]);
                dup2(pipes[i + 1][0], 1);
                close(1);
                parse(cmd[i]);

                _exit(EXIT_SUCCESS);
            } else {
                int status;
                (void) waitpid(pids[i], &status, 0);
            }
        }
        //cmd.clear();
    }
        //коонвеєр^
    else {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            parse(command);

            _exit(EXIT_SUCCESS);
        } else {
            int status;
            (void) waitpid(pid, &status, 0);
        }
    }
    return EXIT_SUCCESS;
}


int main(int argc, char *argv[]) {
    parse:
    DIRECTORY_PATH = (fs::current_path());
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
            if (vector_commands[1][0] == '#') { status = 0; }
            else { status = stoi(vector_commands[1]); }
            return status;
        } else if (vector_commands[0] == "exit")
            return 0;

        start_process(command);
    }

}
