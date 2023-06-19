#ifndef _WELCOME_UI_CPP_
#define _WELCOME_UI_CPP_
#include "UserInterface.cpp"

class WelcomeUI: public UserInterface{
    public:
        void outputField() override{
            frm.title.push_back("Welcome to my Minibase");
            frm.titleFrame();
        }
};
#endif
