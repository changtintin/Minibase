#ifndef _SELECT_PROCESSOR_CPP_
#define _SELECT_PROCESSOR_CPP_
#include <algorithm> 
#include <vector> 
#include "Processor.hpp"
#include "../SystemUser/User.cpp"
#include "../UserInterface/SelectUI.cpp"
#include "../Query/Query.hpp"
#include "../ProcessFile/TableWriteFile.cpp"
#include "../ProcessFile/DataWriteFile.cpp"

class SelectProcessor: public Processor{
    public:
        SelectUI selectUI;

        // select * from tablename
        // select colname from tablename
        Query userQuery;
        
    public:
        void operate(Database &systemDB) override{
            selectUI.iniTableOptions(systemDB);
            output();
            inputLimit = 1;
            receiveQry();
        }

        void output() override{
            selectUI.outputField();
        }

        vector<string> systemSocket() override{
            return inputReply;
        }       
    
    public:
        void selectSpecTb(Database &systemDB);
        void receiveQry();
        void iniQry();
};

void SelectProcessor::iniQry(){
    userQuery.act.clear();
    userQuery.clauseList.clear();
    userQuery.qryList.clear();
    userQuery.qryCols.clear();
    userQuery.rawQry.clear();
    userQuery.tb.clear();
}

void SelectProcessor::selectSpecTb(Database &systemDB){

    //select specific range
    selectUI.fetchPartTb(systemDB, userQuery);    
    iniQry();
}

void SelectProcessor::receiveQry(){
    getline(cin, userQuery.rawQry);
    userQuery.compiler();
}

#endif