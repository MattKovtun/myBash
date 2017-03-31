#include <iostream>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <unistd.h>
#include <sys/wait.h>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <unordered_map>
#include "lsboost.h"
#include "move.h"
#include "remove.h"
#include "cp.h"
#include "mkdir.h"
#include "help.h"
#include "parse.h"
#include <algorithm> // ????
#include <sstream> // ????


#undef BOOST_NO_CXX11_SCOPED_ENUMS
namespace fs = boost::filesystem;
using namespace std;


int start_proccess(string command) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        //      c_args.push_back(0);
        //      execvp(args[0].c_str(), c_args.data());
        //      vector<char*> c_args;

        vector<string> commands = {"ls", "cwd", "md", "rm", "mv", "cp", "mkdir"};
        istringstream buf(command);
        istream_iterator<string> beg(buf), end;
        vector<string> alll(beg, end);
        //пошук наявності команди у всіх командах
        if (find(commands.begin(), commands.end(), alll[0]) != commands.end()) {
            parse(command);
        } else cout << "Command not found" << endl;

        cout << endl;
        _exit(EXIT_SUCCESS);
    } else {
//        printf("Hello from parent\n");
        int status;
        (void) waitpid(pid, &status, 0);
    }
    return EXIT_SUCCESS;
}


int main() {

//    possible_commands.emplace("q", &calc);
//    call_script("q");
    bool quit = false;
    cout << "Welcome to my shell" << endl;
    while (!quit) {
        string command;
        cout << "~ ";
        getline(cin, command);
//        cin >> command;
//        cout << command << endl;
        if (command == "quit") {
            quit = true;
            break;
        }
        start_proccess(command);
    }
}

