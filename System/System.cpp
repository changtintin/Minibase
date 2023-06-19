#ifndef _SYSTEM_CPP_
#define _SYSTEM_CPP_
#include "System.hpp"
#include <typeinfo>
#include <string>

void System::ini(){
    readUserfile.fileAction(systemDB);
    readTbRepofile.fileAction(systemDB);
    readTbsFile.fileAction(systemDB);
}

void System::exitOS(){
    ExitProcessor.operate(systemDB);
    int reply;
    string type = typeid(ExitProcessor.inputReply[0]).name();
    if(type != "i"){
        reply = stoi(ExitProcessor.inputReply[0]);
        if(reply == 1){
            systemDB.passAuth = false;
        }
    }
}

void System::entrOS(){
    entrProcess.operate(systemDB);
}

void System::registOS(){
    registProcess.operate(systemDB);

    // Socket return the user input
    vector<string> registReply = registProcess.systemSocket();
}

void System::loginOS(){
    LoginProcessor.operate(systemDB);
    bool clauseA = LoginProcessor.loginUi.errorTimes < 3;
    bool clauseB = LoginProcessor.loginUi.errorTimes > 0;
    bool clauseC = !systemDB.passAuth;
    if(clauseA && clauseB && clauseC){
        loginOS();
    }
}

void System::authOS(int userReply){
    if(userReply == 1){
        loginOS();        
    }
    else if(userReply == 2){
        registOS();
        loginOS();   
    }
    userReply = 0;
}

void System::receiveQueryOS(){
    QueryProcessor.operate(systemDB);
}

void System::mainOS(){
    ini();
    entrOS();
    int reply = entrProcess.replyIdx();    
    authOS(reply);
    while(systemDB.passAuth){
        receiveQueryOS();
        exitOS();
    }
}
#endif