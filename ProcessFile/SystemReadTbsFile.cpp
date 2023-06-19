#ifndef _SYSTEM_READ_TBS_FILE_CPP_
#define _SYSTEM_READ_TBS_FILE_CPP_
#include "ProcessFile.hpp"

class SystemReadTbsFile: public ProcessFile{

    public:
        virtual void fileAction(Database &systemDB) override{
            fstream openfile;

            // Fetch table names from tableRepo
            for(int tbIdx = 0; tbIdx < systemDB.tableRepo.size(); tbIdx++){
                string fileName = "./SystemFile/" +  systemDB.tableRepo[tbIdx].tbName + ".csv";
                string line, word;

                // Open the table CSV file
                openfile.open (fileName, ios::in);

                showFileStatus(openfile.is_open(), fileName);
                stringstream ss(line);
                vector<string> inputVals;

                // Skip the first row which is the column name
                getline(openfile, line);
                stringstream tmp(line);
                while(getline(tmp, word, ',')){
                    systemDB.tableRepo[tbIdx].colList.push_back(word);
                }

                // Insert the data to Database
                while(getline(openfile, line)){
                    stringstream ss(line);
                    vector<string> inputVals;
                    while(getline(ss, word, ',')){
                        // select table
                        Table desTb = systemDB.tableRepo[tbIdx];

                        // Create the value vector of new row
                        inputVals.push_back(word);
                    }        
                    systemDB.insertRecord(inputVals, systemDB.tableRepo[tbIdx]);
                }
                openfile.clear();
                openfile.close();
            }
        }

    public:
        void showFileStatus(bool fileStatus, string fname);
};

void SystemReadTbsFile::showFileStatus(bool fileStatus, string fname){
    if (!fileStatus) {
        cout << fname << " failed" << endl;
    }
    else{
        cout << fname << " is opened" << endl;
    }
}

#endif
