#ifndef _SYSTEM_READ_TB_REPO_FILE_CPP_
#define _SYSTEM_READ_TB_REPO_FILE_CPP_

#include "ProcessFile.hpp"

class SystemReadTbRepofile: public ProcessFile{
    public:
        virtual void fileAction(Database &systemDB) override{
            fstream openfile;
            string line, word, fname = "./SystemFile/" + systemfile.fileRepo[1];
            openfile.open(fname, ios::in);
            while(getline(openfile, line)){
                Table *readTb = new Table();
                readTb -> tbName = line;
                
                // Store the columns in colList
                systemDB.tableRepo.push_back(*readTb);
            }
            openfile.close();
        }
};
#endif
