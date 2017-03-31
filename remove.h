//
// Created by matt on 3/20/17.
//

#include "asking.h"
bool remove(bool f_ask, bool removing, vector <string> f_files) { // clean
//bool remove(bool f_ask, bool removing, vector <string> f_files) { // clean
    bool answer = true;
    if(!f_ask){
        answer = asking(f_files);
        cout << "ASK"<< endl;
    }if(answer){
        for(auto& s: f_files){
            if(fs::remove_all(s)){
                cout << "Success" << endl;
            } else {
                cout << "Directory not found" << endl;
            }
        }
    }
}
