#ifndef USER_MODULE_H
#define USER_MODULE_H

#include "model.h"

// Function prototypes
UserInfo getUserInfo(); //Done
bool registerUser(UserInfo &user); //Done
std::string getServiceNumber(); //Done
bool isUserExist(const std::string &serviceNumber); //Done
void initialiseUserBill(const std::string &serviceNumber); //Done

#endif
