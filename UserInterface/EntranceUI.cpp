#ifndef _ENTRANCE_UI_CPP_
#define _ENTRANCE_UI_CPP_
#include "UserInterface.cpp"
#include "WelcomeUI.cpp"

class EntranceUI: public UserInterface{
    public: 
        vector<string> options;

    public:
        void outputField() override{
            WelcomeUI wui;
            wui.outputField();
            frm.title.clear();
            frm.title.push_back("Login or Signup");            
            frm.titleFrame();
            showHint();
            showOptions(options);
        }

    public:
        EntranceUI(){
            options.push_back("Login");
            options.push_back("Sign up");
        }
};
#endif
