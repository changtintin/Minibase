#ifndef _EXIT_UI_CPP_
#define _EXIT_UI_CPP_
#include "UserInterface.cpp"
#include "ErrorMsgUI.cpp"

class ExitUI: public UserInterface{
    public:
        ErrorMsgUI errorMsgUI;
        int errorTimes = 3;
        vector<string> options;

        void outputField() override{
            setDefaultOutput();
            frm.title.clear();
            frm.title.push_back("Exit");
            frm.titleFrame();
            showHint();
            showOptions(options);
        }

    public:
        ExitUI(){
            hint = "[ HINT: Go back to main menu or leave ]";
            errorMsgUI.frm.title.push_back("* * Invalid Input * *");
            options.push_back("Exit");
            options.push_back("Back to Main Menu");
        }
};
#endif

