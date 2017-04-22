//
// Created by matt on 3/20/17.
//
#include <iostream>
#include <map>

using namespace std;



namespace fs = boost::filesystem;


string cd(string new_dir){
    if ( new_dir.find("-h") != std::string::npos|| new_dir.find("--help") != std::string::npos){
        cout << "cd <path>  -- перейти до шляху <path>"<< endl;
    }else{
    fs::path src(new_dir);
    chdir(src.c_str());
    fs::path full_path(fs::current_path());
    cout << full_path << '\n';
}}

fs::path pwd(string line) { // Done
    if ( line.find("-h") != std::string::npos|| line.find("--help") != std::string::npos){
        cout << "pwd - вивести поточний шлях "<< endl;
    }else{
    fs::path full_path(fs::current_path());
    cout << "Current path is: " << full_path << endl;
    return full_path;
}}





