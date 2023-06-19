#ifndef _SELECT_UI_CPP_
#define _SELECT_UI_CPP_
#include "InsertUI.cpp"
#include "ErrorMsgUI.cpp"
#include "SelectUI.hpp"
#include <sstream>
using namespace std;

void SelectUI::adjustOutput(){
    cout.width(25);
    cout.setf(ios::left, ios::adjustfield);
}

void  SelectUI::showErrMsg(string msg){
    errorMsgUI.frm.title.push_back(msg);
    errorMsgUI.outputField();
    exit(1);
}

int SelectUI::qryCols(Database &systemDB, vector<string> &selectCols, int tbIdx){
    if(selectCols[0] == "*"){
        return systemDB.tableRepo[tbIdx].colList.size();
    }
    else{
        return selectCols.size();
    }
}

int SelectUI::toInt(string clauseVar){
    stringstream ss(clauseVar);
    int num;
    ss >> num;
    return num;
} 

bool SelectUI::isColExist(Database &systemDB, vector<string> &cols, int tbIdx){
    cout << "isColExist: tbname =" << systemDB.tableRepo[tbIdx].tbName << endl;
    if(cols[0] == "*"){
        return true;
    }
    int limit = systemDB.tableRepo[tbIdx].colList.size();
    int match = 0;
    for(int j = 0; j < cols.size(); j++){
        for(int i = 0; i < limit; i++){
            if(cols[j] == systemDB.tableRepo[tbIdx].colList[i]){
                match ++;
            }
        }
    }
    cout << "match = " << match << ", col.size = " << cols.size() << endl;
    if(match == cols.size()){
        return true;
    }
    else{
        return false;
    }
}

int SelectUI::findTbIdx(Database &systemDB, string tb){
    int limit = systemDB.tableRepo.size();
    for(int i = 0; i < limit; i++){
        if(tb == systemDB.tableRepo[i].tbName){
            return i;
        }
    }
    showErrMsg("Table not exist");
    return -1;
}

// >, <, =, >=, <=, =
bool SelectUI::isOperator(string clauseVar){
    if(clauseVar.length() > 2){
        return 0;
    }
    int match = 0;
    for(int i = 0; i < clauseVar.length(); i++){
        if(clauseVar[i] == '>'){
            match++ ;
        }
        else if(clauseVar[i] == '<'){
            match++ ;
        }
        else if(clauseVar[i] == '='){
            match++ ;
        }
    }
    if(match == clauseVar.length()){
        return 1;
    }
    else{
        return 0;
    }
}

//select * from Student where age > 10 
bool SelectUI::isNumber(string clauseVar){
    for( int i = 0; i < clauseVar.length(); i++ ) {
      if( !isdigit( clauseVar[i] )) {
         return 0;
      }
   }
   return 1;
}

void SelectUI::showColHead(Database &systemDB, Query qry, int tbIdx, int qryColLimit){
    for(int i = 0; i < qryColLimit; i++){
        if(i == 0){
            cout << "|  ";
        }
        adjustOutput();
        if(qry.qryCols[0] == "*"){
            cout << systemDB.tableRepo[tbIdx].colList[i];
        }
        else{
            cout << qry.qryCols[i];
        }        
        cout << "|  ";
    }
    cout << endl;
    for(int i = 0; i < tbLen; i++){
        cout << "-";
    }
    cout << endl;
}

// Print the table name
void SelectUI::showTbName(string tbName){
    cout << "|  TABLE NAME: " + tbName ;
    cout << "|" << endl;
    for(int i = 0; i < tbLen; i++){
        cout << "-";
    }
    cout << endl;
}

void SelectUI::showDivLine(){
    for(int i = 0; i < tbLen; i++){
        cout << "-";
    }
    cout << endl;
}

void SelectUI::fetchPartTb(Database &systemDB, Query qry){
    // Find table idx
    int tbIdx = findTbIdx(systemDB, qry.tb);
    
    // Check col
    if(!isColExist(systemDB, qry.qryCols, tbIdx)){
        showErrMsg("Column not exist");
    }

    // Number of columns in query
    int qryColLimit = qryCols(systemDB, qry.qryCols, tbIdx);

    // Set width of table
    tbLen = 28 * qryColLimit;
    showDivLine();

    // Set the format
    cout.width(tbLen);
    cout.setf(ios::left, ios::adjustfield);
    showTbName(qry.tb);

    // Print the columns
    showColHead(systemDB, qry, tbIdx, qryColLimit);    
    for(int i = 0; i < systemDB.heap.size(); i++){
        if(systemDB.heap[i].tb -> tbName == qry.tb){           
            int colSize = systemDB.tableRepo[tbIdx].colList.size();
            bool matchClause = 0;
            if(qry.clauseList.empty()){                
                matchClause = 1;
            }
            else{
                //Check the col idx
                string clauseCol = qry.clauseList[0];
                int clauseColIdx;
                for(int i = 0; i <  colSize; i++){
                    if(systemDB.tableRepo[tbIdx].colList[i] == clauseCol){
                        clauseColIdx = i;
                        break;
                    }
                    else if(i == colSize - 1){                       
                        showErrMsg("Clause col Error");
                    }
                }

                //Set the variable data type in the clause
                int clauseVarNum;
                string clauseVarStr = "";
                if(!isNumber(qry.clauseList[2])){
                    clauseVarStr = qry.clauseList[2];
                }
                else{
                    clauseVarNum = toInt(qry.clauseList[2]);
                }

                // Check the clause structure                                
                if(systemDB.heap[i].recordData -> blockVals[clauseColIdx] == clauseVarStr){
                    matchClause = 1;
                }
                else if(qry.clauseList[1] == ">" && toInt(systemDB.heap[i].recordData -> blockVals[clauseColIdx]) > clauseVarNum){
                    matchClause = 1;
                }
                else if(qry.clauseList[1] == "<" && toInt(systemDB.heap[i].recordData -> blockVals[clauseColIdx]) < clauseVarNum){
                    matchClause = 1;
                }
                else if(qry.clauseList[1] == "=" && toInt(systemDB.heap[i].recordData -> blockVals[clauseColIdx]) == clauseVarNum){
                    matchClause = 1;
                }           
            }

            // Print the data if meets the limitation of clause
            if(matchClause == 1){          
                for(int p = 0; p < qryColLimit; p++){                           
                    if(p == 0){
                        cout << "|  ";
                    }   
                    if(qry.qryCols[0] == "*"){
                        adjustOutput();
                        cout << systemDB.heap[i].recordData -> blockVals[p];
                        cout << "|  ";
                    }
                    else{
                        for(int j = 0; j < colSize; j++){

                            //Fetch specific column from table
                            if(systemDB.tableRepo[tbIdx].colList[j] == qry.qryCols[p]){   

                                //Print the rows                    
                                adjustOutput();
                                cout << systemDB.heap[i].recordData -> blockVals[j];
                                cout << "|  ";
                            }
                        }
                    }                    
                }
                cout << endl;
            }            
        }
    }
    showDivLine();
    cout << "\n\n\n";
}

#endif

