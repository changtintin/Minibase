#ifndef _USER_INTERFACE_CPP_
#define _USER_INTERFACE_CPP_
#include "UserInterface.hpp"

UserInterface::UserInterface(){
    hint = "[ HINT: Enter the option number ]";
    frm.len = 100;
}

void UserInterface::showHint(){
    cout << hint << endl;
}

void UserInterface::showOptions(vector<string> &options){
    setDefaultOutput();
       
    int insertIdx, limit = options.size();
    for(int i = 0; i < limit; i++){
        cout << setw(5) << "[" << i + 1 << "]   ";
        cout << options[i] << endl << endl;
    }
    cout << quesion << ">>>  ";
}

void UserInterface::setDefaultOutput(){
    cout.width(0);
    cout.unsetf(ios::left);
}
#endif