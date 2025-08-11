#include "user_module.h"
#include <time.h>

UserInfo users[MAX_USERS];
BillInfo bills[MAX_USERS];
int userCount = 0;

char* generateServiceNumber(void) {
    static char serviceNumber[SERVICE_NUMBER_LENGTH];
    srand(time(NULL) + rand());
    
    sprintf(serviceNumber, "%08x-%04x-%04x-%04x-%012x",
            rand(), rand() % 0x10000, rand() % 0x10000,
            rand() % 0x10000, rand());
    
    return serviceNumber;
}

bool registerUser(const char* name, const char* phone, const char* address, char* serviceNumber) {
    if (userCount >= MAX_USERS) {
        return false;
    }
    
    char* genServiceNumber = generateServiceNumber();
    strcpy(serviceNumber, genServiceNumber);
    
    strcpy(users[userCount].name, name);
    strcpy(users[userCount].phone, phone);
    strcpy(users[userCount].address, address);
    strcpy(users[userCount].serviceNumber, serviceNumber);
    
    initialiseUserBill(serviceNumber);
    userCount++;
    
    return true;
}

void initialiseUserBill(const char* serviceNumber) {
    strcpy(bills[userCount].serviceNumber, serviceNumber);
    bills[userCount].currMonthReading = 0.0;
    bills[userCount].prevMonthReading = 0.0;
    bills[userCount].currMonthUsage = 0.0;
    bills[userCount].dues = 0.0;
    bills[userCount].currMonthBill = 0.0;
    bills[userCount].totalAmount = 0.0;
    bills[userCount].lastAmtPaid = 0.0;
}

bool isUserValid(const char* serviceNumber) {
    if (strlen(serviceNumber) != SERVICE_NUMBER_LENGTH - 1) {
        return false;
    }
    
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].serviceNumber, serviceNumber) == 0) {
            return true;
        }
    }
    return false;
}

int findUserIndex(const char* serviceNumber) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(bills[i].serviceNumber, serviceNumber) == 0) {
            return i;
        }
    }
    return -1;
}
