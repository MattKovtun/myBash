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
#include "help.h"

#undef BOOST_NO_CXX11_SCOPED_ENUMS
namespace fs = boost::filesystem;
using namespace std;


bool asking_cp() {
    char type;
    while (!cin.fail() && type != 'y' && type != 'n') {
        cout << " <-- Do you want to copy these files? y/n " << endl;
        cin >> type;
    }
    return type == 'y' ? true : false;
}

void _cp_copy(string s, fs::path destination_path, bool ask) {
    fs::path source_path(s);
	//! Вам самим як читати той рядок, що нижче? ;-)
    if (fs::is_directory(destination_path))destination_path /= source_path.filename();
    ask = ( !ask ? asking_cp() : true); // ask = (ask == false ? asking_cp() : true);
    if (ask) {
        try {
            fs::copy_file(source_path, destination_path, fs::copy_option::overwrite_if_exists);
            cout << "Success" << endl;
        }
        catch (...) {
            cout << "No such file " << s << endl;
        }
    }
}

int main(int argc, const char *argv[]) {
    vector<string> to_cp;

    bool h = false;
    for (int i = 1; i < argc; i++) {
        if (!h) h = (argv[i] == string("-h") ? true : false);
        if (!h) h = (argv[i] == string("--help") ? true : false);
		//! Якщо знайшли, можна цикл зразу і перервати. Або, краще, вивести допомогу і вийти, а не мучити той прапорець.
    }
    if (h) {
        helping(4);
        return 0;
    }
    bool answerF = false;
    for (int i = 1; i < argc; i++) {
        //if (!answerF)answerF = (argv[i] == string("-f") ? true : false); // Ну що за масло масляне постійно?!
        if (!answerF)
				answerF = (argv[i] == string("-f") );
			
        if (argv[i] != string("-f"))
			to_cp.push_back(string(argv[i]));
    }

	//! Ну, Ви сформували to_cp і?
	//! Та ну...
    fs::path destination_path(argv[argc - 2]);  //        ????????
    for (int i = 1; i < argc - 1; ++i) { // ???????????????
		//! Просто щоб Ви побачили глибину Вашого падіння, додав вивід що і куди воно копіює
		cout << "File: " << argv[i] << " to " << destination_path << endl;
        _cp_copy(argv[i], destination_path, answerF);
    }
}
