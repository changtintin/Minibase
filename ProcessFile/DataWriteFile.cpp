#ifndef _DATA_WRITE_FILE_CPP_
#define _DATA_WRITE_FILE_CPP_
#include "ProcessFile.hpp"

class DataWriteFile: public ProcessFile{
    public: 
        int tbIdx;
    public:
        virtual void fileAction(Database &systemDb) override{
            ofstream openTb;
            string tb = systemDb.tableRepo[tbIdx].tbName;
            string fileName = "./SystemFile/" + tb + ".csv";
            openTb.open (fileName, ios::app);
            int limit = systemDb.tableRepo[tbIdx].colList.size();
            int recordIdx = systemDb.heap.size();
            openTb << "\n";
            for(int i = 0; i < limit; i++){
                openTb << systemDb.heap[recordIdx - 1].recordData -> blockVals[i];
                if(i != limit - 1){
                    openTb << ",";
                }
            }
            openTb.close();
        }
};
#endif
