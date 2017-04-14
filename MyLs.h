//
// Created by natasha on 06.04.17.
//

#ifndef MYBASH_MYLS_H
#define MYBASH_MYLS_H

#endif //MYBASH_MYLS_H

using namespace std;
namespace fs = boost::filesystem;

#include <boost/regex.hpp>

//отримати розмір папки
void  getFoldersize(string rootFolder,unsigned long long & f_size)
{
    fs:: path folderPath(rootFolder);
    if (exists(folderPath)) {
        fs:: directory_iterator end_itr;
        for (fs::directory_iterator dirIte(rootFolder); dirIte != end_itr; ++dirIte ){
            fs::path filePath(complete (dirIte->path(), folderPath));
            try{if (!is_directory(dirIte->status()) ) f_size = f_size + file_size(filePath);
                else getFoldersize(filePath.string(),f_size);
            }catch(exception& e){  cout << e.what() << endl; }
        }
    }
}
//отримати розмір з викликом попередньої функції
unsigned long long getSize(fs:: path a){
    unsigned long long  f_size;
    if(fs::is_directory(a)){
        f_size = 0;
        getFoldersize(a.string(),f_size);//попередня функція
    }else{f_size = fs::file_size(a);}// бустівська функція для файлу
    return  f_size;
}
//функції для порівняння в сорт(нижче)
bool less_Size(fs::path a,fs:: path b){//за розміром S
    return  getSize(a) < getSize(b);
}

bool less_Time (fs::path a,fs:: path b){ //за часом ост модифікафії t
    std::time_t timeA = boost::filesystem::last_write_time(a) ;
    std::time_t timeB = boost::filesystem::last_write_time(b) ;
    return std::ctime( &timeA ) < std::ctime( &timeB);
}

bool less_Extension(fs::path a,fs:: path b) { // за розширенням X
    return a.extension() < b.extension();
}

//самая главная фунция, прінт, парс за видом сорту
void printMapLs(const multimap<time_t, fs::path> &m, bool answerL ,string sorting ,bool answerReverse) {
    vector <fs::path> vector1;
    for (auto elem : m) {
        vector1.push_back(elem.second);
    }

    if (sorting == "S"){
        sort (vector1.begin(), vector1.end(), less_Size);
    }if(sorting == "t"){
        sort (vector1.begin(), vector1.end(), less_Time);
    }if(sorting == "X"){
        sort (vector1.begin(), vector1.end(), less_Extension);
    }
    if (sorting == "N"){
        sort (vector1.begin(), vector1.end());
    }
    if(answerReverse){
        std::reverse(vector1.begin(),vector1.end());
    }
    for(int i = 0; i < vector1.size(); i++){
    if(answerL){
        std::time_t t = boost::filesystem::last_write_time(vector1[i]);
        if(fs::is_directory(vector1[i]))cout<<"/" << vector1[i].filename().string() << " size: " <<getSize(vector1[i]) <<" time last modification: " << std::ctime( &t )<< endl;
        else cout<< vector1[i].filename().string() << " size: " <<getSize(vector1[i]) <<" time last modification: " << std::ctime( &t )<< endl;
    }else{
        if(fs::is_directory(vector1[i]))cout<<"/" << vector1[i].filename().string()<<endl;
        else cout<< vector1[i].filename().string() << endl;
    }
    }
}


//маска(знайшла в неті)

vector< std::string > mask(const std::string target_path, const boost::regex my_filter ){
    std::vector< std::string > all_matching_files;
    fs::directory_iterator end_itr; // Default ctor yields past-the-end
    for( fs::directory_iterator i( target_path ); i != end_itr; ++i )
    { if( !boost::filesystem::is_regular_file( i->status() ) ) continue;
        boost::smatch what;
        if( !boost::regex_match(  i->path().filename().string(), what, my_filter ) ) continue;
        all_matching_files.push_back( i->path().string());
    }
    return  all_matching_files;
}

//

//це парс для printMap і отримування файлів з директорії

multimap<time_t, fs::path> lsDir(fs::path someDir, const boost::regex my_filter){
    fs::directory_iterator end_iter;
    typedef multimap<time_t, fs::path> result_set_t;
    result_set_t result_set;
    const boost::regex m("0");
    if (fs::exists(someDir) && fs::is_directory(someDir)) {
        for (fs::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter) {
            if( my_filter == m){result_set.insert(result_set_t::value_type(fs::last_write_time(dir_iter->path()), *dir_iter));}
            else {
                std::vector< std::string > a = mask(someDir.string(), my_filter);
                mask(someDir.string(), my_filter);
                if(find(a.begin(), a.end(), *dir_iter) != a.end()){
                    result_set.insert(result_set_t::value_type(fs::last_write_time(dir_iter->path()), *dir_iter));
                }
            }
        }
    }
    return result_set;
};

void ls(int argc, const char *argv[]) {
    fs::path someDir;
    typedef multimap<time_t, fs::path> result_set_t;
    result_set_t result_set;
    vector <string> flagsLs = {"-l", "-h", "--sort=U", "--sort=S", "--sort=t", "--sort=X", "-r"};
    if (argc != 2&& find(flagsLs.begin(), flagsLs.end(), argv[1]) == flagsLs.end()) {// перевірка чи перший ел це диреткорія (або маска)
        if (fs::is_directory(argv[1])){
            someDir = argv[1];// це директорія !!!
            if (argc > 3 && find(flagsLs.begin(), flagsLs.end(), argv[2]) == flagsLs.end()) {
                const boost::regex my_filter1(argv[2]);
                result_set = lsDir(someDir, my_filter1);
            }
            else{
                const boost::regex my_filter2("0");
                result_set = lsDir(someDir, my_filter2);
                cout << someDir.string() <<endl;
            }
        }
        else {
            const boost::regex my_filter3(argv[1]);
            result_set = lsDir(fs::current_path(), my_filter3);
        }
    }else{
        const boost::regex my_filter4("0");
        result_set= lsDir(fs::current_path(), my_filter4);
    }


    //парс
    bool answerL = false;
    string sorting = "N";
    bool answerReverse = false;
    for (int i = 1; i < argc - 1; i++) {
        if(!answerL)answerL = (argv[i] == string("-l") ? true : false);
        if(!answerReverse)answerReverse = (argv[i] == string("-r") ? true : false);
        if(sorting == "N") sorting = (argv[i] == string ("--sort=U")? "U" : "0");
        if(sorting == "N") sorting = (argv[i] == string ("--sort=S")? "S" : "0");
        if(sorting == "N") sorting = (argv[i] == string ("--sort=t")? "t" : "0");
        if(sorting == "N") sorting = (argv[i] == string ("--sort=X")? "X" : "0");
    }
    printMapLs(result_set, answerL, sorting, answerReverse);

    /*const boost::regex my_filter( "r.*.txt" );
    mask("/home/natasha", my_filter);*/
    }


// ls [якісь букви] -- будь-який набір з цих букв (можна і менше, можна більше)
//ls [mBashyYtujv]
//myBash

// ls якісьбукви.* -- замість крапки-зірка що-небудь
//ls m.*
//myBash.cbp
//myBash

// ls (що-небудь)+ -- плюс гарантує хоча б одне входження виражу в дужках (або якщо немає дужок то ост буква)
//наприклад, ab+c -- abc abbbc abbc АЛЕ НЕ  ac
//ls myBash(.cbp)+
//myBash.cbp

//https://habrahabr.ru/post/115825/
