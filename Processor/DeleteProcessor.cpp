#ifndef _DELETE_PROCESSOR_CPP_
#define _DELETE_PROCESSOR_CPP_
#include <iostream>
#include <algorithm> 
#include <vector> 
#include <cstdio>
#include <stdio.h>
#include "Processor.hpp"
#include "../SystemUser/User.cpp"
#include "../UserInterface/DeleteUI.cpp"
#include "../Query/Query.hpp"
#include "../ProcessFile/TableRepoDelFile.cpp"
#include "../ProcessFile/SystemReadTbRepofile.cpp"
#include "../ProcessFile/SystemReadTbsFile.cpp"

class DeleteProcessor: public Processor{
    public:
        DeleteUI deleteUI;
        TableRepoDelFile tableRepoDelFile;
        SystemReadTbRepofile sysReadTbRepoFile;
        SystemReadTbsFile sysReadTbsFile;              
        
    public:
        void operate(Database &systemDB) override{
            deleteUI.iniTableOptions(systemDB);
            output();
            inputLimit = 1;
            input();
        }

        void output() override{
            deleteUI.outputField();
        }

        vector<string> systemSocket() override{
            return inputReply;
        }    

    protected:
        void iniDb(Database &systemDB);

    public:
        int findTb(Database &systemDB, string tb);
        void delTbCsv(Database &systemDB, string tb);
        void deleteTb(Database &systemDB);       
};

void DeleteProcessor::iniDb(Database &systemDB){
    // deallocate the memory of the vector
    vector<Table>().swap(systemDB.tableRepo);

    // clear the contents of the vector
    systemDB.tableRepo.clear();

    vector<Record>().swap(systemDB.heap);
    systemDB.heap.clear();

    vector<Page>().swap(systemDB.pageRepo);
    systemDB.pageRepo.clear();

    Page iniPage;
    systemDB.pageRepo.push_back(iniPage);
    systemDB.curPageIdx = 0;
}

int DeleteProcessor::findTb(Database &systemDB, string tb){
    int s = systemDB.tableRepo.size();
    for(int i = 0; i < s; i++){
        if(tb == systemDB.tableRepo[i].tbName){
            return i;
        }
    }
    return -1;
}

void DeleteProcessor::delTbCsv(Database &systemDB, string tb){
    char *file = new char(100);
    string s = "./SystemFile/" + tb + ".csv";
    strcpy(file, s.c_str());

    //remove() return false if it success
    int delResult = remove(file);
    if(delResult){
        deleteUI.errorMsgUI.frm.title.push_back("Delete Failed");
        deleteUI.errorMsgUI.outputField();
    }
    else{
        deleteUI.errorMsgUI.frm.title.push_back("Delete Successful");
        deleteUI.errorMsgUI.outputField();
    }
}

void DeleteProcessor::deleteTb(Database &systemDB){
    if(!inputReply.empty()){
        int tableIdx = toInt(inputReply[0]);
        string tb = deleteUI.options[tableIdx - 1];
        tableIdx = findTb(systemDB, tb);
        if(tableIdx != -1){                        
            delTbCsv(systemDB, tb);
            tableRepoDelFile.tbRepoDelFile(systemDB, tb);          
            iniDb(systemDB); 
            sysReadTbRepoFile.fileAction(systemDB);
            sysReadTbsFile.fileAction(systemDB);            
        }
    }
}

#endif