#ifndef _REGISTER_UI_CPP_
#define _REGISTER_UI_CPP_
#include "UserInterface.cpp"
#include "ErrorMsgUI.cpp"

class RegisterUI: public UserInterface{
    public:
        ErrorMsgUI errorMsgUI;

        void outputField() override{
            frm.title.clear();
            frm.title.push_back("Registration");
            frm.titleFrame();
            showHint();
            quesion = "Set the account name and password";
            cout << quesion << ">>>  ";
        }

    public:
        RegisterUI(){
            hint = "[ HINT: The account and password should be different ]";
            errorMsgUI.frm.title.push_back("* * Both of the inputs can't be empty * *");
        }
};
#endif