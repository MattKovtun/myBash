//
// Created by matt on 3/20/17.
//
#ifndef MYBASH_MOVE_H
#define MYBASH_MOVE_H

#endif //MYBASH_MOVE_H


#include <iostream>
#include <map>

using namespace std;



namespace fs = boost::filesystem;

void printMap(const multimap<time_t, fs::path> &m) {
    for (auto elem : m) {
        std::cout << elem.second << "\n";
    }
}
string cd(string new_dir){
    /*fs::path src(new_dir);
    fs::current_path(src);
    cout << fs::current_path() << '\n';*/
}

string cwd() { // Done
    fs::path full_path(fs::current_path());
    cout << "Current path is: " << full_path << endl;}


void ls_boost() {  // Done

    string direct = cwd();
    fs::path someDir(direct);
    fs::directory_iterator end_iter;

    typedef multimap<time_t, fs::path> result_set_t;
    result_set_t result_set;

    if (fs::exists(direct) && fs::is_directory(direct)) {
        for (fs::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter) {
            if (fs::is_regular_file(dir_iter->status())) {
                result_set.insert(result_set_t::value_type(fs::last_write_time(dir_iter->path()), *dir_iter));
            }
        }
    }
    printMap(result_set);

}


