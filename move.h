//
// Created by natasha on 3/20/17.
//

////////////////////////////////////////////////////////////
/////////////////DONE///////////////DONE////////////////////
////////////////////////////////////////////////////////////



bool askingg(string d){
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

void _copy(string s, fs::path dest, bool more_than_one_file, bool ask) {
    fs::path src(s);
    if (more_than_one_file)dest /= src.filename();
    if(fs::exists(dest)){
        if(!ask){
            ask = askingg("rename");
        }
    }else{ask = true;}

    if(ask){
        try {
            fs::rename(src, dest);
            cout << "Success" << endl;
        }
        catch (...) {
            cout << "No such file " << s << endl;
        }}
}


int move(int argc, const char *argv[]) {
    bool more_than_one_file = false;
    bool answerF = false;
    for (int i = 1; i < argc-1; i++){
        if(argv[i] == string("-f")){
            answerF = true;}}
    if (argc > 4 + int(answerF)) more_than_one_file = true;

    fs::path dest(argv[argc - 2]);  //        ????????
    for (int i = 1; i < argc - 2; ++i) { // ???????????????
        if (argv[i] != string("-f")){
            _copy(argv[i], dest, more_than_one_file, answerF);}
    }
}
