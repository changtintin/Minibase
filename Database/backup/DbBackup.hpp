#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <iostream>
#include <vector>
#include <utility> // std::pair, std::make_pair
#include <map>

#include "../SystemUser/User.cpp"
using namespace std;
class Table{
    public:
        string tbName;
        vector<string> colList;
};

class RowData{
    public:
        vector<string> blockValList;
};

class DataBlock{
    public:
        //unique
        Table *tbPtr;
        
        //string = index
        //Rowdata = vector of colname and data
        pair<string, RowData> block;
    public:
        void newBlock(Table &ptr, pair<string, RowData> p);
};
void DataBlock::newBlock(Table &ptr, pair<string, RowData> p){
    tbPtr = &ptr;
    block = p;
}

class Page{
    public: 
        vector<DataBlock*> pageBlocks;
    public:
};

class PageRepo{
    public:
        vector<Page> pgList;
        int pgIdx;
        int blockIdx;
        int pgStoreLimit;

    public:
        PageRepo();

    public:
        void flipPg();
};

PageRepo::PageRepo(){
    pgIdx = 0;
    blockIdx = 0;
    pgStoreLimit = 5;
}

void PageRepo::flipPg(){
    Page newPage;
    pgList.push_back(newPage);
    pgIdx++;
}

class Database{
    public:
        string dbName;
        bool passAuth;
        //Datablock* = Record
        vector<DataBlock*> heap;
        PageRepo pageRepo;
        vector<User> userList;
        vector<Table> tableRepo;
    
    public: 
        Database();
    
    public:
        void showpgList();
        void showHeap();
        void createNewRow(vector<string> &colList, int tbIdx);
        string createblockIdx();
};

Database::Database(){
    passAuth = false;
}
#endif