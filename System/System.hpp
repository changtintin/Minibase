#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <iostream>
#include <vector>
#include <time.h>    
#include <string>
#include <map>

#include "../Processor/EntranceProcessor.cpp"
#include "../Processor/RegisterProcessor.cpp"
#include "../Processor/LoginProcessor.cpp"
#include "../Processor/QueryProcessor.cpp"
#include "../Processor/ExitProcessor.cpp"
#include "../Database/Database.cpp"
#include "../UserInterface/WelcomeUI.cpp"
#include "../UserInterface/ExitUI.cpp"
#include "../ProcessFile/SystemReadUserfile.cpp"
#include "../ProcessFile/SystemReadTbRepofile.cpp"
#include "../ProcessFile/SystemReadTbsFile.cpp"

class System{
    public:
        Database systemDB;
        EntranceProcessor entrProcess;
        RegisterProcessor registProcess;
        LoginProcessor LoginProcessor;
        QueryProcessor QueryProcessor;
        ExitProcessor ExitProcessor;       
        SystemReadUserfile readUserfile;
        SystemReadTbRepofile readTbRepofile;
        SystemReadTbsFile readTbsFile;
        WelcomeUI wui;
        ExitUI exitUI;        
    
    public:
        void ini();
        void backToMain();
        void mainOS();
        void entrOS();
        void registOS();
        void loginOS();
        void exitOS();
        void authOS(int userReply);
        void receiveQueryOS();
};

#endif