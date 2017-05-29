//
// Created by natasha on 06.04.17.
//


#ifndef  MV_MyLs_H
#define MV_MyLs_H
using namespace std;
namespace fs = boost::filesystem;

#include <boost/regex.hpp>
#include <iomanip>
#include "help.h"


//отримати розмір папки
void  getFoldersize(string rootFolder,unsigned long long & f_size);
//отримати розмір з викликом попередньої функції


unsigned long long getSize(fs:: path a);
//функції для порівняння в сорт(нижче)
bool less_Size(fs::path a,fs:: path b);

bool less_Time (fs::path a,fs:: path b);

bool less_Extension(fs::path a,fs:: path b) ;

//самая главная фунция, прінт, парс за видом сорту
void printMapLs(const multimap<time_t, fs::path> &m, bool answerL ,string sorting ,bool answerReverse);


//маска(знайшла в неті)

vector< std::string > mask(const std::string target_path, const boost::regex my_filter );

//це парс для printMap і отримування файлів з директорії

multimap<time_t, fs::path> lsDir(fs::path someDir, const boost::regex my_filter);

void ls(int argc, const char *argv[]) ;


// ls [якісь букви]+ -- будь-який набір з цих букв
//ls [mBashyYtujv]+
//myBash


// ls якісьбукви.* -- спочатку ці букви, а замість крапки-зірка що-небудь
//ls m.*
//myBash.cbp
//myBash

// ls (якісьбукви)+ -- плюс гарантує хоча б одне входження виразу в дужках (або якщо немає дужок то входження останньої букви перед *)
//наприклад, ab+c -- abc abbbc abbc АЛЕ НЕ  ac
//ls myBash(.cbp)+
//myBash.cbp

// ls якісьбукви? -- знак запитання гарантує одне або нуль потраплянь букви перед ? (не більше)
//ls /home/natasha/Test  baaaa?ba.txt (4 a)
//baaaba.txt (3 a)


// ls ^буква{кількість разів} або  ^буква{від, до}-- ця буква трапиться стільки разів
//ls /home/natasha/Test ^a{5}.txt
//aaaaa.txt
// ls /home/natasha/Test  ^a{2,7}.txt
// aaaaa.txt
//ls /home/natasha/Test  ^a{6}.txt
//нічого

//http://www.boost.org/doc/libs/1_55_0/libs/regex/doc/html/boost_regex/syntax/perl_syntax.html
#endif