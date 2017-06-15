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



    //коментарі
    long index = command.find("#");
    if(index != -1) {
        string sub_str2 = command.substr (0, index);
        command = sub_str2;}
    //коментарі ^
    // конвеєр
    vector<string> strings;
    istringstream f(command);
    string s;
    vector<string> cmd;

    //змінні середовища
    //export VAR=ABCC
    if (command.find("export") != -1){
        size_t found = command.find("=");
        command.replace(0, 7, "");
        if (found!=-1){
            string namVar = command.substr(0,found-7);
            string var = command.substr(found-6, command.length());
            setenv(namVar.c_str(), var.c_str(), true);
            cout << namVar << ", " << var << endl;
        }
        return 1;
    }
    //
    while (getline(f, s, '|')) {
        strings.push_back(s);
        cmd.push_back(s);
    }
    //коонвеєр^

        pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if(cmd.size() >=2){
        int pipefd[2];
        pipe(pipefd);
        //for(int i = 0; i < cmd.size() -1;){

        if (pid == 0) {
//            vector<const char *> c_args;
//            istringstream buf(cmd[0]);
//            istream_iterator<string> beg(buf), end;
//            vector<string> tokens(beg, end);
//            c_args = create_c(tokens, tokens[0]);

            close(pipefd[0]);
            dup2(pipefd[0], 0);
//
//
//            if(tokens[0] == "mkdir" || tokens[0] == "rm" || tokens[0] == "cp" || tokens[0] == "ls"){
//                string s = DIRECTORY_PATH.string() + "/" + tokens[0];
//
//                const char *path = s.c_str();
//                execvp(path, const_cast<char *const *>( c_args.data()));
//                perror("Failed to start excec");}
//            else{
//                execvp(c_args[0], const_cast<char *const *>( c_args.data()));
//                perror("Failed to start your command.");
//                cout << " But we can help you: " << endl;
//            }
            parse(cmd[0]);
            close(pipefd[1]);
            _exit(EXIT_SUCCESS);
        } else {
            int status;
            (void) waitpid(pid, &status, 0);

//            vector<const char *> c_args_1;
//            istringstream buf(cmd[1]);
//            istream_iterator<string> beg(buf), end;
//            vector<string> tokens(beg, end);
//            c_args_1 =create_c(tokens, tokens[0]);


            close(pipefd[1]);
            dup2(pipefd[1], 1);

//            if(tokens[0] == "mkdir" || tokens[0] == "rm" || tokens[0] == "cp" || tokens[0] == "ls"){
//            string s = DIRECTORY_PATH.string() + "/" + tokens[0];
//
//            const char *path = s.c_str();
//            execvp(path, const_cast<char *const *>( c_args_1.data()));
//            perror("Failed to start excec");}
//            else{
//                cout << c_args_1[0] << endl;
//                execvp(c_args_1[0], const_cast<char *const *>( c_args_1.data()));
//                perror("Failed to start your command.");
//            }
            parse(cmd[1]);
            close(pipefd[0]);
            _exit(EXIT_SUCCESS);
        }
        //cmd.clear();
    }
    else{ if (pid == 0) {
//        istringstream buf(command);
//        vector<const char *> c_args;
//        istream_iterator<string> beg(buf), end;
//        vector<string> tokens(beg, end);

        parse(command);

        _exit(EXIT_SUCCESS);
    } else {
        int status;
        (void) waitpid(pid, &status, 0);
    }}
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
