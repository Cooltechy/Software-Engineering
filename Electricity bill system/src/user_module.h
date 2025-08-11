#ifndef USER_MODULE_H
#define USER_MODULE_H

#include "types.h"

// Function prototypes
char* generateServiceNumber(void);
bool registerUser(const char* name, const char* phone, const char* address, char* serviceNumber);
void initialiseUserBill(const char* serviceNumber);
bool isUserValid(const char* serviceNumber);

#endif
