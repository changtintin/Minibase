#ifndef _ADMIN_CPP_
#define _ADMIN_CPP_
#include "SystemUser.hpp"
class Admin: public SystemUser{
    protected:
        string adminToken;
};

#endif