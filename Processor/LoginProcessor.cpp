#ifndef _LOGIN_PROCESSOR_CPP_
#define _LOGIN_PROCESSOR_CPP_

#include <algorithm> 
#include <vector> 

#include "Processor.hpp"
#include "../UserInterface/LoginUI.cpp"
#include "../SystemUser/User.cpp"

class LoginProcessor: public Processor{
    public:
        LoginUI loginUi;
        
    public:
        void operate(Database &systemDB) override{
            output();
            inputLimit = 3;
            input();
            if(isValid(inputReply[0]) && isValid(inputReply[1])){
                if(authLogin(systemDB, inputReply)){
                    authResult("Login Successful");
                    systemDB.passAuth = true;
                }
                else{                    
                    if(loginUi.errorTimes == 0){
                        exit(1);
                    }
                    loginUi.errorMsgUI.outputField();
                    loginUi.errorTimes --;
                }
            }
            else{
                loginUi.errorMsgUI.outputField();
                loginUi.errorTimes --;
            }
        }

        void output() override{
            loginUi.outputField();
        }

        vector<string> systemSocket() override{
            return inputReply;
        }   

    public:
        bool isValid(string input);
        bool authLogin(Database systemDB, vector<string> &registReply);
        void authResult(string result);
};

bool LoginProcessor::isValid(string input){
    if(input.length() >= 5){
        return 1;
    }
    return 0;
}

bool LoginProcessor::authLogin(Database systemDB, vector<string> &registReply){
    int listSize = systemDB.userList.size();
    if(listSize > 0){
        for(int i = 0; i < listSize; i++){
            bool clauseA = systemDB.userList[i].user[0] == registReply[0];
            bool clauseB = systemDB.userList[i].user[1] == registReply[1];
            bool clauseC = systemDB.userList[i].user[2] == registReply[2];
            if(clauseA && clauseB && clauseC){
                return 1;
            }
        }
        return 0;
    }
    return 0;   
}

void LoginProcessor::authResult(string result){
    loginUi.frm.title.clear();
    loginUi.frm.title.push_back(result);
    loginUi.frm.msgFrame();
}
#endif