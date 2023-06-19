#ifndef _USER_CPP_
#define _USER_CPP_
#include "SystemUser.hpp"

class User: public SystemUser{
    protected:
        string userToken;

    public:

        // username, password, loginToken
        void createUser(string n, string p, string t){
            user.push_back(n);
            user.push_back(p);
            user.push_back(t);
        }
};
#endif

