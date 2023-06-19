#ifndef _LOGIN_UI_CPP_
#define _LOGIN_UI_CPP_
#include "UserInterface.cpp"
#include "ErrorMsgUI.cpp"

class LoginUI: public UserInterface{
    public:
        ErrorMsgUI errorMsgUI;
        int errorTimes = 3;

        void outputField() override{
            LoginTimes();
            frm.title.push_back("Sign in");
            frm.titleFrame();
            showHint();
            quesion = "Enter the account name, password, user token";
            cout << quesion << ">>>  ";
        }

    public:
        LoginUI(){
            hint = "[ HINT: The account and password length > 5 characters ]";
            errorMsgUI.frm.title.push_back("* * Invalid username or password or  user token * *");
        }
    
    public:
        void LoginTimes(){
            string err = "You have " + to_string(errorTimes) + " chances";
            frm.title.push_back(err);
            frm.msgFrame();
            frm.title.clear();
        }
};
#endif

