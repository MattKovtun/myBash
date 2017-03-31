//
// Created by matt on 3/20/17.
//

////////////////////////////////////////////////////////////
/////////////////DONE///////////////DONE////////////////////
////////////////////////////////////////////////////////////


void _copy(string s, fs::path dest, bool more_than_one_file) {
    fs::path src(s);

    if (more_than_one_file)dest /= src.filename();
    try {
        fs::rename(src, dest);
        cout << "Success" << endl;
    }
    catch (...) {
        cout << "No such file " << s << endl;
    }
}


int move(int argc, const char *argv[]) {
    bool more_than_one_file = false;
    if (argc > 4) more_than_one_file = true;
    fs::path dest(argv[argc - 2]);  //        ????????
    for (int i = 1; i < argc - 2; ++i) { // ???????????????
        _copy(argv[i], dest, more_than_one_file);
    }
}
