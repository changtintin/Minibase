#ifndef _DATABASE_CPP_
#define _DATABASE_CPP_

#include <iterator> 
#include "Database.hpp"

void Database::showpgList(){
    cout << "pageRepo size: " << pageRepo.pgList.size() << endl;
    for(int i = 0; i < pageRepo.pgIdx; i++){
        cout << "page " << i << ": " << endl;
        int blockNum = pageRepo.pgList[i].pageBlocks.size();
        
        for(int j = 0; j < blockNum; j++){
            cout << "\t";
            for(int f = 0; f < pageRepo.pgList[i].pageBlocks[j]->block.second.blockValList.size(); f++){
                cout << pageRepo.pgList[i].pageBlocks[j]->block.second.blockValList[f]<< " ";
            }
            cout << endl;
        }
    }
}

void Database::showHeap(){
    cout << "heap size: " << heap.size() << endl;
    for(int i = 0; i < heap.size(); i++){
        int limit = heap[i]->block.second.blockValList.size();
        cout << "\t";
        for(int j = 0; j < limit; j++){
            cout << heap[i]->block.second.blockValList[j] << " ";
        }
        cout << endl;
    }
}

void Database::createNewRow(vector<string> &colList, int tbIdx){
    Page p;
    RowData newRow;
    string tb = tableRepo[tbIdx].tbName;
    Table * tbRef = new Table();
    tbRef = &tableRepo[tbIdx];
    DataBlock *newBlock = new DataBlock();
    newRow.blockValList = colList;
    pair<string, RowData> newPr(createblockIdx(), newRow);
    newBlock -> block = newPr;
    newBlock -> tbPtr = tbRef;
    p.pageBlocks.push_back(newBlock);                                        
    heap.push_back(newBlock);    
    if(p.pageBlocks.size() == 5){
        pageRepo.pgList.push_back(p);
        pageRepo.pgIdx ++;
        pageRepo.blockIdx = 0;
        p.pageBlocks.clear();
    }
    else{
        pageRepo.pgList[pageRepo.pgIdx].pageBlocks[pageRepo.blockIdx] = newBlock;
    }
   
    showpgList();
}

string Database::createblockIdx(){
    //initialize random seed
    srand (time(NULL));

    //generate secret number between 1 and 10000
    int idx = rand() % 10000 + 1;
    string newIdx = to_string(idx);
    return newIdx;
}

#endif