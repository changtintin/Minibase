#ifndef _USERINTERFACE_H_
#define _USERINTERFACE_H_

#include <iostream>
#include <vector>
#include <iomanip>

#include "../Frame/Frame.cpp"

using namespace std;
class UserInterface{
    public:
        int width;
        Frame frm;
        string hint;
        string quesion;
        vector<string>  title;
       
    public:
        virtual void outputField() = 0;

    public:
        UserInterface();
        void showHint();
        void showOptions(vector<string> &content);
        void setDefaultOutput();
};
#endif