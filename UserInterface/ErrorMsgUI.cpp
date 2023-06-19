#ifndef _ERROR_MSG_UI_CPP_
#define _ERROR_MSG_UI_CPP_
#include "UserInterface.cpp"

class ErrorMsgUI: public UserInterface{
    public:
        void outputField() override{
            frm.msgFrame();
        }
};
#endif