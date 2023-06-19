#ifndef _ENTRANCE_PROCESSOR_CPP_
#define _ENTRANCE_PROCESSOR_CPP_

#include "Processor.hpp"
#include "../Database/Database.hpp"
#include "../UserInterface/EntranceUI.cpp"

class EntranceProcessor: public Processor{
    public:
        EntranceUI entrance;
    public:
        void operate(Database &systemDB) override{
            output();
            inputLimit = 1;
            input();   
        }

        void output() override{
            entrance.outputField();
        }

        vector<string> systemSocket() override{
            return inputReply;
        }        
    public: 
        int replyIdx();
};

int EntranceProcessor::replyIdx(){
    return stoi(inputReply[0]);
}

#endif
