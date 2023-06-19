#ifndef _REGISTER_PROCESSOR_CPP_
#define _REGISTER_PROCESSOR_CPP_

#include "Processor.hpp"
#include "../UserInterface/RegisterUI.cpp"
#include "../ProcessFile/RegistWriteFile.cpp"

class RegisterProcessor: public Processor{
    public:
        RegisterUI registUi;
        RegistWriteFile registWriteFile;

    public:
        void operate(Database &systemDB) override{
            output();
            inputLimit = 2;
            input();
            if(isValid(inputReply[0]) && isValid(inputReply[1])){                           
                addUser(systemDB, inputReply);
                registUi.frm.title.clear();                
                int userIdx = systemDB.userList.size() - 1;
                string t = systemDB.userList[userIdx].user[2];
                registUi.frm.title.push_back("Register Successful");
                registUi.frm.title.push_back("Here is your token: "+ t);
                registUi.frm.msgFrame();
            }
            else{
                registUi.errorMsgUI.outputField();
            }
        }

        void output() override{
            registUi.outputField();
        }

        vector<string> systemSocket() override{
            return inputReply;
        }  

    public:     
        bool isValid(string input);
        int createToken();
        void addUser(Database &systemDB, vector<string> &registReply); 
};

//input string length more than 5 characters
bool RegisterProcessor::isValid(string input){
    if(input.length() >= 5){
        return 1;
    }
    return 0;
}

int RegisterProcessor::createToken(){
    
    //initialize random seed
    srand (time(NULL));

    //generate secret number between 1 and 1000
    return rand() % 1000 + 1;
}

void RegisterProcessor::addUser(Database &systemDB, vector<string> &registReply){

    // Add new user to user list
    string token = to_string(createToken());        
    User newUser;
    newUser.createUser(registReply[0], registReply[1], token);
    systemDB.userList.push_back(newUser);
    registWriteFile.fileAction(systemDB);
}

#endif
