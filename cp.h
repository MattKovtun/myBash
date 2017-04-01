//
// Created by matt on 3/20/17.
//

#ifndef MYBASH_CP_H
#define MYBASH_CP_H

#endif //MYBASH_CP_H

//cp /home/natasha/Test/test.txt /home/natasha/Test/test_2.txt /home/natasha/Bash

bool asking_cp(string d){
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

void _cp_copy(string s, fs::path destination_path, bool more_than_one_file, bool ask) {
    fs::path source_path(s);
    if (more_than_one_file)destination_path /= source_path.filename();
    if(fs::exists(destination_path)){
        if(!ask){
            ask = asking_cp("copy");
        }
    }else{ask = true;}

    if(ask){
        try {
            fs::copy_file(source_path, destination_path, fs::copy_option::overwrite_if_exists);
            cout << "Success" << endl;
        }
        catch (...) {
            cout << "No such file " << s << endl;
        }}
}

bool cp(int argc, const char *argv[]) {
    bool more_than_one_file = false;
    bool answerF = false;
    for (int i = 1; i < argc-1; i++){
        if(argv[i] == string("-f")){
            answerF = true;}}
    if (argc > 4 + int(answerF)) more_than_one_file = true;

    fs::path destination_path(argv[argc - 2]);  //        ????????
    for (int i = 1; i < argc - 2; ++i) { // ???????????????
        if (argv[i] != string("-f")){
            _cp_copy(argv[i], destination_path, more_than_one_file, answerF);}
    }

}
