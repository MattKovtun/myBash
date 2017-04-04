//
// Created by matt on 3/20/17.
//

////////////////////////////////////////////////////////////
/////////////////DONE///////////////DONE////////////////////
////////////////////////////////////////////////////////////


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
    if (fs::is_directory(destination_path))destination_path /= source_path.filename();
    ask = (ask == false ? asking_cp() : true);
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

int cp(int argc, const char *argv[]) {
    vector<string> to_cp;
    bool answerF = false;
    for (int i = 1; i < argc - 1; i++) {
        answerF = (argv[i] == string("-f") ? true : false);
        if (argv[i] != string("-f"))to_cp.push_back(string(argv[i]));
    }

    fs::path destination_path(argv[argc - 2]);  //        ????????
    for (int i = 1; i < argc - 2; ++i) { // ???????????????
        _cp_copy(argv[i], destination_path, answerF);

    }
}
