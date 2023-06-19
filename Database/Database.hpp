#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <fstream>
#include <iostream> 
#include <sstream>
#include <vector>

#include "Page.hpp"
#include "Record.hpp"
#include "Table.hpp"
#include "../SystemUser/User.cpp"

using namespace std;
class Database{
    public:
        // Limitation of datablocks in a page
        int pageStorageLimit;
        bool passAuth;
        vector<Record> heap;

        // Index of current page
        int curPageIdx;

        // Pages of pageRepo
        vector<Page> pageRepo; 
        vector<Table> tableRepo;
        vector<User> userList;

    public:
        Database();
        void searchRecord(string value);
        void insertRecord(vector<string>& value, Table &tb);
        void createPage();
        int createblockIdx();
        void fetchAllRecord(); 
        void fetchAllPages();
        void fetchDbSchema();
};

#endif