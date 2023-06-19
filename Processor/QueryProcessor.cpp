#ifndef _QUERY_PROCESSOR_CPP_
#define _QUERY_PROCESSOR_CPP_
#include <algorithm> 
#include <vector> 
#include "Processor.hpp"
#include "InsertProcessor.cpp"
#include "SelectProcessor.cpp"
#include "DeleteProcessor.cpp"
#include "../UserInterface/QueryUI.cpp"
#include "../UserInterface/SelectUI.cpp"
#include "../UserInterface/InsertUI.cpp"
#include "../SystemUser/User.cpp"
#include "../Query/Query.hpp"

class QueryProcessor: public Processor{
    public:
        QueryUI queryUI;
        SelectUI selectUI;
        InsertUI insertUI;
        InsertProcessor InsertProcessor;
        SelectProcessor SelectProcessor;
        DeleteProcessor DeleteProcessor;
        
    public:
        void operate(Database &systemDB) override{
            output();
            inputLimit = 1;
            input();
            routeQry(systemDB);
        }

        void output() override{
            queryUI.outputField();
        }

        vector<string> systemSocket() override{
            return inputReply;
        }   

    public:
        bool isValid();
        void routeQry(Database &systemDB);
        void selectQryOperate(Database &systemDB);
        void insertQryOperate(Database &systemDB);
        void deleteQryOperate(Database &systemDB);
        // void updateQryOperate();
        // void alterQryOperate();
};

bool QueryProcessor::isValid(){
    cout << "ok" << endl;
    return 1;
}

void QueryProcessor::selectQryOperate(Database &systemDB){
    SelectProcessor.operate(systemDB);
    SelectProcessor.selectSpecTb(systemDB);
}

void QueryProcessor::insertQryOperate(Database &systemDB){
    
    InsertProcessor.operate(systemDB);  
    int reply = toInt(InsertProcessor.inputReply[0]);
    if(reply == 1){
        // Choose table
        InsertProcessor.insertTbData(systemDB);
    }
    else if(reply == 2){
        // Create table
        InsertProcessor.createTb(systemDB);
    }  
}

void QueryProcessor::deleteQryOperate(Database &systemDB){
    DeleteProcessor.operate(systemDB);
    DeleteProcessor.deleteTb(systemDB);
}

void QueryProcessor::routeQry(Database &systemDB){
    int reply = stoi(inputReply[0]);
    switch (reply){
        //Select
        case 1:
            selectQryOperate(systemDB);
            break;

        //Insert
        case 2:
            insertQryOperate(systemDB);
            break;

        // //Delete
        case 3:
            deleteQryOperate(systemDB);
            break;

        // //Update
        // case 4:
        //     updateQryOperate();
        //     break;
        
        // //Alter
        // case 5:
        //     alterQryOperate();
        //     break;
        default:
            break;
    }
}

#endif