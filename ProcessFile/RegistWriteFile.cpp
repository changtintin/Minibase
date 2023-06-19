#ifndef _REGIST_WRITE_FILE_CPP_
#define _REGIST_WRITE_FILE_CPP_
#include "ProcessFile.hpp"

class RegistWriteFile: public ProcessFile{
    public:
        virtual void fileAction(Database &systemDb) override{
            int limit =  systemDb.userList.size() - 1;
            string fname = "./SystemFile/" + systemfile.fileRepo[0];
            ofstream openTb;
            openTb.open (fname, ios::app);
            openTb << systemDb.userList[limit].user[0] << ",";
            openTb << systemDb.userList[limit].user[1] << ",";
            openTb << systemDb.userList[limit].user[2] << "\n";
            openTb.close();
        }
};
#endif
