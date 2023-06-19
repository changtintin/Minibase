#ifndef _PAGE_H_
#define _PAGE_H_

#include <iostream>
#include <vector>

#include "DataBlock.hpp"

using namespace std;
class Page{
    public:
        int blockIdx;
        vector<DataBlock*> pageContent; 
        
    public:
        Page();
        DataBlock* createDatablock(int createId, vector<string> &createVal);
};

Page::Page(){
    blockIdx = 0;
};

DataBlock* Page::createDatablock(int createId, vector<string> &createVal){
    DataBlock *newBlock = new DataBlock(createId, createVal);
    pageContent.push_back(newBlock);
    return newBlock;
}

#endif

