#ifndef _TABLE_REPO_DEL_FILE_CPP_
#define _TABLE_REPO_DEL_FILE_CPP_
#include "ProcessFile.hpp"
#include "TableWriteFile.cpp"
#include<iostream>
class TableRepoDelFile: public TableWriteFile{
    public:
        virtual void fileAction(Database &systemDb) override{
            cout << "ok" << endl;
        }
        
    public:
        // Rewrite data into TableRepo.csv
        void tbRepoDelFile(Database &systemDb, string tb){            
            fstream openTb;
            stringstream ss;
            string line, word;
            string fname = "./SystemFile/TableRepo.csv";                                    
            openTb.open (fname, ios::in);
            while(getline(openTb, line)){
                if(line != tb){
                    ss << line;
                    ss << "\n";
                }
            }
            openTb.clear();
            openTb.close();

            openTb.open (fname, ios::out|ios::ate);
            while(getline(ss, word)){
                openTb << word << "\n";                
            }
            openTb.clear();
            openTb.close();
        }
};
#endif

