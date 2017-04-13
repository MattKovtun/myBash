//
// Created by natasha on 06.04.17.
//

#ifndef MYBASH_MYLS_H
#define MYBASH_MYLS_H

#endif //MYBASH_MYLS_H



using namespace std;



namespace fs = boost::filesystem;

void printMapLs(const multimap<time_t, fs::path> &m, bool answerL ,string sorting ,bool answerReverse) {
    for (auto elem : m) {
        std::time_t t = boost::filesystem::last_write_time(elem.second) ;
        if(fs::is_directory(elem.second)){std::cout <<"/"<< elem.second.filename().string() <<  "\n";}
        else{std::cout << elem.second.filename().string()  << "\n";}
        //fs:: file_size(elem.second)   розмір файлу!! папки?
        //std::time_t t = boost::filesystem::last_write_time(elem.second) ; std::ctime( &t ); дістати час модифікації

    }
}


void ls(int argc, const char *argv[]) {
    fs::path someDir;
    vector <string> flagsLs = {"-l", "-h", "--sort=U", "--sort=S", "--sort=t", "--sort=X", "-r"};
    if (argc != 2&& find(flagsLs.begin(), flagsLs.end(), argv[1]) == flagsLs.end()){
        someDir = argv[1];}
    else{someDir = pwd();}
    fs::directory_iterator end_iter;
    typedef multimap<time_t, fs::path> result_set_t;
    result_set_t result_set;
    if (fs::exists(someDir) && fs::is_directory(someDir)) {
        for (fs::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter) {
                result_set.insert(result_set_t::value_type(fs::last_write_time(dir_iter->path()), *dir_iter));
        }
    }
    bool answerL = false;
    string sorting = "0";
    bool answerReverse = false;
    for (int i = 1; i < argc - 1; i++) {
        if(!answerL)answerL = (argv[i] == string("-l") ? true : false);
        if(!answerReverse)answerReverse = (argv[i] == string("-r") ? true : false);
        if(sorting == "0") sorting = (argv[i] == string ("--sort=U")? "U" : "0");
        if(sorting == "0") sorting = (argv[i] == string ("--sort=S")? "S" : "0");
        if(sorting == "0") sorting = (argv[i] == string ("--sort=t")? "t" : "0");
        if(sorting == "0") sorting = (argv[i] == string ("--sort=X")? "X" : "0");
    }
    //cout << answerL << ", " << answerReverse << ", "<< sorting <<"!"<< endl;
    printMapLs(result_set, answerL, sorting, answerReverse);
    }