#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>    
#include "../Database/Database.hpp"
using namespace std;

class Processor{
    public:
        int inputLimit;
        vector<string> inputReply;

    public:
        virtual void operate(Database &systemDB) = 0;
        virtual void output() = 0;
        virtual vector<string> systemSocket() = 0;

        void input(){
            if(!inputReply.empty()){
                inputReply.clear();
            }
            int c = 0;
            string tmp;
            while(c < inputLimit){
                getline(cin, tmp);
                inputReply.push_back(tmp);
                c++;
            }       
        }

        int toInt(string str){
            stringstream ss(str);
            int num;
            ss >> num;
            return num;
        }
};

#endif