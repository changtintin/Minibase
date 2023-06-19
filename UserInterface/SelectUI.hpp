#ifndef _SELECT_UI_H_
#define _SELECT_UI_H_
#include "InsertUI.cpp"
#include "ErrorMsgUI.cpp"
#include "../Query/Query.hpp"
#include "../Database/Database.hpp"
using namespace std;

class SelectUI: public InsertUI{
    public:
        ErrorMsgUI errorMsgUI;
        int errorTimes = 3;
        int tbLen;

        void outputField() override{
            frm.title.clear();
            frm.title.push_back("Select");
            frm.titleFrame();
            hint = "[ HINT: Table List ]";
            showHint();
            showOptions(options);
        }

    public:
        SelectUI(){
            quesion = "QUERY FORMAT:  select * / COLUMN NAME from TABLE NAME where CLAUSE";
            errorMsgUI.frm.title.push_back("* * Invalid Format, Please check again * *");
        }
    
    protected:
        int findTbIdx(Database &systemDB, string tb);
        bool isColExist(Database &systemDB, vector<string> &cols, int tbIdx);
        bool isNumber(string clauseVar);
        bool isOperator(string clauseVar);           
        int qryCols(Database &systemDB, vector<string> &cols, int tbIdx);
        int toInt(string clauseVar);
        
    public:        
        void adjustOutput();        
        void fetchPartTb(Database &systemDB, Query qry);    
        void showTbName(string tbName);
        void showErrMsg(string msg);
        void showColHead(Database &systemDB, Query qry, int tbIdxm, int qryColLimit); 
        void showDivLine();
};

#endif