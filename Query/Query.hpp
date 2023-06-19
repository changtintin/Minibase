#ifndef _QUERY_H_
#define _QUERY_H_

#include <iostream>
#include <vector>
class Query{
    public:
        // select _ from ______ where ______
        string rawQry;

        // * or colnames
        vector<string> qryCols;

        // table name
        string tb;
        string act;
        vector<string> clauseList;
        vector<string> qryList;
        vector<string> actList;

    public:
        Query();

    protected:
        void setqryCols();
        void setTb();
        void setAction();
        void setClause();

    public:
        void compiler();
};
Query::Query(){
    actList.push_back("select");
    actList.push_back("insert");
    actList.push_back("delete");
    actList.push_back("update");
    actList.push_back("alter");
}

void Query::setAction(){
    int qryLen = qryList.size();
    int actLen = actList.size();
    for(int i = 0; i < qryLen; i++){
        for(int j = 0; j < actLen; j++){
            if(qryList[i] == actList[j]){
                act = qryList[i];
                qryList.erase(qryList.begin());
            }
        }
    }
}

void Query::setTb(){
    tb = qryList.front();
    qryList.erase(qryList.begin());
}

void Query::setqryCols(){
    int qryLen = qryList.size();
    int idx = 0;

    for(int i = 0; i < qryLen; i++){
        if(qryList[i] == "from"){
            break;
        }
        qryCols.push_back(qryList[i]);
        idx++;
    }
    for(int i = 0; i <= idx; i++){
        qryList.erase(qryList.begin());
    }
}

void Query::setClause(){
    int qryLen = qryList.size();    
    int idx = 0;
    for(int i = 1; i < qryLen; i++){
        clauseList.push_back(qryList[i]);
        cout << qryList[i] << endl;
        idx++;
    }
}

void Query::compiler(){
    if(rawQry.length() != 0){   

        // split the query into words             
        string str = rawQry;      
        int strlen = str.length();
        string word;
        while(str.find(" ") != std::string::npos){
            size_t found = str.find(" ");
            word = str.substr(0, found);
            str = str.substr(found + 1, strlen - found);
            qryList.push_back(word);
        }
        qryList.push_back(str);
        setAction();
        setqryCols();
        setTb();
        setClause();
    }
    else{
        cout << "Error" << endl;
    }
}

#endif