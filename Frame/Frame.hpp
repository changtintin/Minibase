#ifndef _FRAME_H_
#define _FRAME_H_

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
class Frame{
    public:
        int len;
        int width;
        vector<string> title;

    public: 
        void titleFrame();
        void msgFrame();
        void duoLine();
        void dottedLine();
        void content();
};


#endif
