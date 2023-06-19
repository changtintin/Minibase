#ifndef _QUERY_UI_CPP_
#define _QUERY_UI_CPP_

#include "UserInterface.cpp"
#include "ErrorMsgUI.cpp"

class QueryUI: public UserInterface{
    public:
        ErrorMsgUI errorMsgUI;
        int errorTimes = 3;
        vector<string> options;

        void outputField() override{
            frm.title.clear();
            frm.title.push_back("Query Types");
            frm.titleFrame();
            showHint();
            showOptions(options);
        }

    public:
        QueryUI(){
            hint = "[ HINT: Enter the option number ]";
            errorMsgUI.frm.title.push_back("* * Invalid option choosed * *");
            options.push_back("Select");
            options.push_back("Insert");
            options.push_back("Delete");
            options.push_back("Update");
            options.push_back("Alter");
        }
};
#endif

