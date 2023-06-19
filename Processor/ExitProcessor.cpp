#ifndef _EXIT_PROCESSOR_CPP_
#define _EXIT_PROCESSOR_CPP_
#include "Processor.hpp"
#include "../Database/Database.hpp"
#include "../UserInterface/ExitUI.cpp"

class ExitProcessor: public Processor{
    public:
        ExitUI exitUI;
    public:
        void operate(Database &systemDB) override{
            output();
            inputLimit = 1;
            input();   
        }

        void output() override{
            exitUI.outputField();
        }

        vector<string> systemSocket() override{
            return inputReply;
        }     
};
#endif
