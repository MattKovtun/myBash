#include <iostream>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <unistd.h>
#include <sys/wait.h>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <unordered_map>
#include "help.h"

#include "lsboost.h"
#include "move.h"
#include "remove.h"
#include "cp.h"
#include "mkdir.h"
#include "TODO.h"
#include "MyLs.h"
#include "parse.h"


#undef BOOST_NO_CXX11_SCOPED_ENUMS
namespace fs = boost::filesystem;
using namespace std;
vector<string> commands = {"ls", "pwd", "md", "rm", "mv", "cp", "mkdir", "cd", "TODO"};

int start_proccess(string command) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {

        istringstream buf(command);
        istream_iterator<string> beg(buf), end;
        vector<string> vector_commands(beg, end);
        if (find(commands.begin(), commands.end(), vector_commands[0]) != commands.end()) { //пошук наявності команди у всіх командах
            parse(command);
        } else cout << "Command not found" << endl;

//        cout << endl;
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
    cout << "Welcome to my shell! Type : \"mkdir -h\" for example, to see help!\nType \"TODO\" to see problems to be solved." << endl;
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

