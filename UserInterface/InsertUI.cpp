#ifndef _INSERT_UI_CPP_
#define _INSERT_UI_CPP_

#include "UserInterface.cpp"
#include "ErrorMsgUI.cpp"
#include "../Database/Database.hpp"

class InsertUI: public UserInterface{
    public:
        ErrorMsgUI errorMsgUI;
        int insertTimes;
        vector<string> options;

        void outputField() override{
            frm.title.clear();
            frm.title.push_back("Insert");
            frm.titleFrame();
            showHint();
            showOptions(options);
        }

    public:
        InsertUI(){
            iniInsertOptions();
            errorMsgUI.frm.title.push_back("* * Invalid input * *");
        }
    public:
        void iniTableOptions(Database &systemDB);
        void iniInsertOptions();
        void setInsertTimes();
        void insertSelectTb(Database &systemDB);
        void insertData(Database &systemDB, int tbIdx);
        void hintColList(vector<string> &colList);        
};

void InsertUI::iniTableOptions(Database &systemDB){
    options.clear();
    int limit = systemDB.tableRepo.size();
    for(int i = 0; i < limit; i ++){
        options.push_back(systemDB.tableRepo[i].tbName);
    }
    hint = "[ HINT: select a table ]";
}

void InsertUI::iniInsertOptions(){
    options.clear();
    options.push_back("Choose a Table");
    options.push_back("Create a Table");
    hint = "[ HINT: Choose a Table or create one]";
}

void InsertUI::insertSelectTb(Database &systemDB){
    iniTableOptions(systemDB);
    outputField();
    iniInsertOptions();
}

void InsertUI::hintColList(vector<string> &colList){
    for(int i = 0; i < colList.size(); i++){
        hint += colList[i];
        if(i !=  colList.size() - 1){
            hint += " / ";
        }
    }
    hint += " ] ";
}

void InsertUI::insertData(Database &systemDB, int tbIdx){
    //Find the col name
    hint = "[ HINT: Data should be seperated by comma \nEnter the data of columns: ";
    hintColList(systemDB.tableRepo[tbIdx].colList);
    options.clear();
    outputField();
    iniInsertOptions();
}

#endif

