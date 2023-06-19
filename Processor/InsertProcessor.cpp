#ifndef _INSERT_PROCESSOR_CPP_
#define _INSERT_PROCESSOR_CPP_
#include <algorithm> 
#include <sstream>
#include <vector> 
#include <string>
#include "Processor.hpp"
#include "../SystemUser/User.cpp"
#include "../UserInterface/InsertUI.cpp"
#include "../Query/Query.hpp"
#include "../ProcessFile/TableWriteFile.cpp"
#include "../ProcessFile/DataWriteFile.cpp"

class InsertProcessor: public Processor{
    public:
        InsertUI insertUI;
        vector<string> newdata;
        DataWriteFile dataWrite;
        TableWriteFile tableWrite;
        
    public:
        void operate(Database &systemDB) override{
            output();
            inputLimit = 1;
            input();
        }

        void output() override{
            insertUI.outputField();
        }

        vector<string> systemSocket() override{
            return inputReply;
        }   

    protected:
        int findTb(Database &systemDB, string tb);        

    public:
        // bool isValid(Database &systemDB, string tbName);
        void insertTbData(Database &systemDB);
        void createTb(Database &systemDB);
        void addcolList(Database &systemDB, int numCol);
};

int InsertProcessor::findTb(Database &systemDB, string tb){
    int s = systemDB.tableRepo.size();
    for(int i = 0; i < s; i++){
        if(tb == systemDB.tableRepo[i].tbName){
            return i;
        }
    }
    return -1;
}

void InsertProcessor::insertTbData(Database &systemDB){
    
    //Select Table
    insertUI.insertSelectTb(systemDB);
    input();
    int tableIdx = toInt(inputReply[0]);
    string tb = insertUI.options[tableIdx - 1];
    tableIdx = findTb(systemDB, tb);
    Table * tptr= new Table();
    tptr = &systemDB.tableRepo[tableIdx];

    //Insert input data
    insertUI.insertData(systemDB, tableIdx);
    inputLimit = systemDB.tableRepo[tableIdx].colList.size();
    inputReply.clear();
    string tmp, word;
    getline(cin, tmp);
    stringstream ss;
    ss << tmp;
    while(getline(ss, word, ',')){
        newdata.push_back(word);
    }
    systemDB.insertRecord(newdata, *tptr);
    dataWrite.tbIdx = tableIdx;
    dataWrite.fileAction(systemDB);
}

void InsertProcessor::addcolList(Database &systemDB, int numCol){
    insertUI.hint = "[ HINT: Table Name and Columns]";
    output();
    inputLimit = numCol;
    string input;
    vector<string> newcolList;

    //Table Name
    Table newTb;
    for(int i = 0; i < inputLimit; i++){
        getline(cin, input);
        if(i == 0){
            newTb.tbName = input;
        }
        else{
            newTb.colList.push_back(input);
        }
    }
    systemDB.tableRepo.push_back(newTb);
}

void InsertProcessor::createTb(Database &systemDB){
    insertUI.options.clear();
    insertUI.hint = "[ HINT: num of columns ]";
    output();
    inputLimit = 1;
    input();
    int numcolList = stoi(inputReply[0]) + 1;
    addcolList(systemDB, numcolList);
    TableWriteFile tbWriteFile;

    //open a new csv file and write the colList in
    tbWriteFile.fileAction(systemDB);

    //write table name and colList to the TableRepo file
    tbWriteFile.tbRepoWriteFile(systemDB);
    insertUI.iniInsertOptions();
}

#endif