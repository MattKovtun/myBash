//
// Created by natasha on 4/1/17.
//


//#include "asking.h"


#ifndef MYBASH_REMOVE_H
#define MYBASH_REMOVE_H

#endif //MYBASH_REMOVE_H

bool asking(string d){
    bool answer;
    char type;
    while( !cin.fail() && type!='y' && type!='n' ){
        cout<< "<-- Do you want to  " << d << " this files? y/n " <<endl;
        cin >> type;
    }
    if(type == 'y'){
        answer = true;
    }else{
        answer = false;
    }
    return answer;
}
bool remove(int argc, const char *argv[]) { // Done

    bool answerF = false;
    bool answerR = false;
    for (int i = 1; i < argc-1; i++){
        if(argv[i] == string("-f")){
            answerF = true;
        }if(argv[i] == string("-R")){
            answerR = true;
        }
    }
    if (!answerF){answerF = asking("delete");}

    for (int i = 1; i < argc - 1; ++i) {
        if(answerF && argv[i] != string("-f") && argv[i] != string("-R")){
            if(answerR == false && fs:: is_directory(argv[i])){
                cout<< "You can't remove directories --> "<< argv[i]<<endl;}
            else{
                if(fs::remove_all(argv[i])){
                    cout << "Success" << endl;
                } else {
                    cout << "Directory not found" << endl;
                }}
        }
    }
}
