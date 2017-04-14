//
// Created by natasha on 3/20/17.
//

////////////////////////////////////////////////////////////
/////////////////DONE///////////////DONE////////////////////
////////////////////////////////////////////////////////////



bool asking_rename() {
    char type;
    while (!cin.fail() && type != 'y' && type != 'n') {
        cout << " <-- Do you want to rename these files? y/n " << endl;
        cin >> type;
    }
    return type == 'y' ? true : false; }

void _copy(string s, fs::path dest, bool ask) {
    fs::path src(s);
    if (fs::is_directory(dest))dest /= src.filename();
    ask = (ask == false ? asking_rename() : true);
    if (ask) {
        try {
            fs::rename(src, dest);
            cout << "Success" << endl;
        }
        catch (...) {
            cout << "No such file " << s << endl;
        }
    }
}


int move(int argc, const char *argv[]) {
    vector<string> to_rename_move;
    bool answerF = false;
    for (int i = 1; i < argc - 2; i++) {
        if(!answerF)answerF = (argv[i] == string("-f") ? true : false);
        if (argv[i] != string("-f"))to_rename_move.push_back(string(argv[i]));
    }
    fs::path dest(argv[argc - 2]);  //        ????????
    for (int i = 0; i < to_rename_move.size(); ++i) { // ???????????????
        _copy(to_rename_move[i], dest,  answerF);

    }
}
