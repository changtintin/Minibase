#ifndef _RECORD_H_
#define _RECORD_H_

#include <iostream> 

#include "Table.hpp"
#include "DataBlock.hpp"

using namespace std;

// a record point to a datablock
class Record{
    public:
    
        // Change pointer point to a datablock
        DataBlock *recordData; 
        Table *tb;

    public:
        Record(DataBlock *ptrB, Table *ptrTb);
};

Record :: Record(DataBlock *ptrB, Table *ptrTb){
    recordData = ptrB;
    tb = ptrTb;
};

#endif