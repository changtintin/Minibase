#ifndef _PROCESSFILE_H_
#define _PROCESSFILE_H_

#include <iostream>
#include <sstream>
#include <fstream>

#include "../Database/Database.hpp"
#include "../File/File.hpp"
#include "../Database/Database.hpp"


using namespace std;

class ProcessFile{
    public:
        File systemfile;
    
    public:    
        ProcessFile(){
            systemfile.fileRepo.push_back("Users.csv");
            systemfile.fileRepo.push_back("TableRepo.csv");
        }
        virtual void fileAction(Database &systemDb) = 0;
};

#endif