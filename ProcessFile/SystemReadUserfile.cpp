#ifndef _SYSTEM_READ_USER_FILE_CPP_
#define _SYSTEM_READ_USER_FILE_CPP_

#include "ProcessFile.hpp"

class SystemReadUserfile: public ProcessFile{
    public:
        virtual void fileAction(Database &systemDB) override{
            fstream openfile;
            string line, word, fname = "./SystemFile/" + systemfile.fileRepo[0];
            

            // Open the table CSV file
            openfile.open (fname, ios::in);

            if (!openfile.is_open()) {
                cout << "Failed" << endl;
            }

            getline(openfile, line);

            // Skip the first row which is the column name
            while(getline(openfile, line)){
                stringstream ss(line);
                User u;

                // save user info in systemDB.userList
                while(getline(ss, word, ',')){
                    u.user.push_back(word);
                }
                systemDB.userList.push_back(u);                
            }            
            openfile.close();
        }
};
#endif
