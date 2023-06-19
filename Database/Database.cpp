#ifndef _DATABASE_CPP_
#define _DATABASE_CPP_
#include <iterator> 
#include "Database.hpp"

Database::Database(){
    curPageIdx = 0;
    pageStorageLimit = 5;
    passAuth = false;
    Page iniPage;
    pageRepo.push_back(iniPage);
}

void Database::insertRecord(vector<string>& value, Table &tb){  
    int curPageSize = pageRepo[curPageIdx].pageContent.size();
    if(curPageSize == pageStorageLimit){
        createPage();
        curPageIdx ++;
    }
    int randId = createblockIdx();
    DataBlock *blockRef = pageRepo[curPageIdx].createDatablock(randId, value);
    Record newRecord(blockRef, &tb);
    heap.push_back(newRecord);
}

void Database::fetchAllRecord(){
    cout << "## HEAP ##" << endl;
    if(!heap.empty()){
        cout << endl;
        for(int i = 0; i < heap.size(); i++){
            int dataIdx = heap[i].recordData->blockVals.size();
            cout << "[  ";
            for(int j = 0; j < dataIdx; j++){
                cout << heap[i].recordData->blockVals[j];
                if(j != dataIdx - 1){
                    cout << " , ";
                }
            }
            cout << "  ]" << endl;
        }
        cout << endl;
    }
}

void Database::createPage(){
    Page newPage;
    pageRepo.push_back(newPage);
}

void Database::fetchAllPages(){
    cout << "## PAGE REPO ##" << endl;
    for(int p = 0; p <= curPageIdx; p++){
        cout << "p. " << p << endl;
        for(int b = 0; b < pageRepo[p].pageContent.size(); b++){
            cout << "[ " << pageRepo[p].pageContent[b] -> index << " -> ";
            int limit = pageRepo[p].pageContent[b] -> blockVals.size();
            for(int i = 0; i < limit; i++){
                cout << pageRepo[p].pageContent[b]->blockVals[i];
                if(i != limit - 1){
                    cout << " , ";
                }
            }
            cout << " ]" <<  endl;
        }
        cout << endl;
    }
}

int Database::createblockIdx(){
    //generate secret number between 1 and 10000
    int idx = rand() % 10000 + 1;
    return idx;
}

void Database::fetchDbSchema(){
    cout << "## Database Schema ##" << endl;
    int s = tableRepo.size();
    for(int i = 0; i < s; i++){
        cout << tableRepo[i].tbName << " ---> ";
        int cols = tableRepo[i].colList.size();
        for(int j = 0; j < cols; j++){
            cout << tableRepo[i].colList[j];
            if(j != cols - 1){
                cout << ", ";
            }
        }
        cout << endl;
    }
}

#endif