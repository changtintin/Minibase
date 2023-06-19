#ifndef _TABLE_WRITE_FILE_CPP_
#define _TABLE_WRITE_FILE_CPP_
#include "ProcessFile.hpp"

class TableWriteFile: public ProcessFile{
    public:
        //open a new csv file and write the colList in
        virtual void fileAction(Database &systemDb) override{
            int idxTb =  systemDb.tableRepo.size() - 1;
            string fname = "./SystemFile/" + systemDb.tableRepo[idxTb].tbName + ".csv";
            int idxCol = systemDb.tableRepo[idxTb].colList.size();
            ofstream openTb;
            openTb.open (fname, ios::app);
            for(int i = 0; i < idxCol; i++ ){
                openTb << systemDb.tableRepo[idxTb].colList[i];
                if(i != idxCol - 1){
                    openTb << ",";
                }
            }
            openTb.close();            
        }
        
    public:
        //write table name to the TableRepo file
        void tbRepoWriteFile(Database &systemDb){
            int idxTb =  systemDb.tableRepo.size() - 1;

            //open TableRepo
            string fname = "./SystemFile/" + systemfile.fileRepo[1];
            int idxCol = systemDb.tableRepo[idxTb].colList.size();
            ofstream openTb;
            openTb.open (fname, ios::app);

            //write table name
            openTb << systemDb.tableRepo[idxTb].tbName;
            openTb << "\n";
            openTb.close();
        }
};
#endif
