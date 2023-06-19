#ifndef _DATABLOCK_H_
#define _DATABLOCK_H_

#include <vector>
using namespace std;

class DataBlock{
    public:
        int index;
        vector<string> blockVals;
    public:
        DataBlock(int createId, vector<string>& createVal);
};

DataBlock::DataBlock(int createId, vector<string>& createVal){
    index = createId;
    copy(createVal.begin(), createVal.end(), back_inserter(blockVals)); 
};

#endif