//
// Created by matt on 3/23/17.
//

#ifndef MYBASH_ASKING_H
#define MYBASH_ASKING_H

#endif //MYBASH_ASKING_H
bool asking(vector <string> f_files){
    bool answer;
    char type;
    do
    {
        for (std::vector<string>::const_iterator i = f_files.begin(); i != f_files.end(); ++i)
            std::cout << *i << ' ';
        cout<< "<-- Do you want to delete this files? y/n " <<endl;
        cin >> type;
    }
    while( !cin.fail() && type!='y' && type!='n' );
    if(type == 'y'){
        answer = true;
    }else{
        answer = false;
    }
    return answer;
};
