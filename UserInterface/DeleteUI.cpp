#ifndef _DELETE_UI_CPP_
#define _DELETE_UI_CPP_
#include "ErrorMsgUI.cpp"
#include "../Database/Database.hpp"

#include <sstream>
using namespace std;

class DeleteUI: public UserInterface{
    public:
        ErrorMsgUI errorMsgUI;
        int insertTimes;
        vector<string> options;

        void outputField() override{
            frm.title.clear();
            frm.title.push_back("Delete");
            frm.titleFrame();
            showHint();
            showOptions(options);
        }
    public:
        void iniTableOptions(Database &systemDB){
            options.clear();
            int limit = systemDB.tableRepo.size();
            for(int i = 0; i < limit; i ++){
                options.push_back(systemDB.tableRepo[i].tbName);
            }
            hint = "[ HINT: select a table ]";
        }
};




#endif

