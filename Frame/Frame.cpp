#ifndef _FRAME_CPP_
#define _FRAME_CPP_

#include "Frame.hpp"

void Frame::duoLine(){
    for(int i = 0; i <= len; i++){
        cout << "=";
    }
    cout << endl;
}

void Frame::dottedLine(){
    for(int i = 0; i <= len; i++){
        cout << "-";
    }
    cout << endl;
}

void Frame::content(){
    width = title.size();
    for(int i = 0; i < width; i++){
        int space = (len - title[i].length()) / 2;
        cout << "|";
        cout << setw(len - space) << title[i] << setw(space);
        cout << "|";
        if(i != width - 1){
            cout << endl;
        }
    }
    cout << endl;
}

void Frame::titleFrame(){
    cout << "\n\n";
    duoLine();
    content();
    duoLine();
    cout << "\n\n";
}

void Frame::msgFrame(){
    cout << "\n\n";
    dottedLine();
    content();
    dottedLine();
    cout << "\n\n";
}
#endif