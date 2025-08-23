#include "user_module.h"
#include <time.h>
#include "../../fileHandling/fileUtils.h"

#define USERS_FILE "users.dat"
#define BILLS_FILE "bills.dat"

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

bool saveDataToFiles(void) {
    // Save users data
    FILE* usersFile = openFile(USERS_FILE, "wb");
    if (!usersFile) {
        printf("Error: Unable to create users file for saving.\n");
        return false;
    }
    
    // Write user count first
    if (fwrite(&userCount, sizeof(int), 1, usersFile) != 1) {
        printf("Error: Failed to write user count to file.\n");
        fclose(usersFile);
        return false;
    }
    
    // Write all users
    if (userCount > 0) {
        if (fwrite(users, sizeof(UserInfo), (size_t)userCount, usersFile) != (size_t)userCount) {
            printf("Error: Failed to write users data to file.\n");
            fclose(usersFile);
            return false;
        }
    }
    fclose(usersFile);
    
    // Save bills data
    FILE* billsFile = openFile(BILLS_FILE, "wb");
    if (!billsFile) {
        printf("Error: Unable to create bills file for saving.\n");
        return false;
    }
    
    // Write bills data (userCount should match)
    if (userCount > 0) {
        if (fwrite(bills, sizeof(BillInfo), (size_t)userCount, billsFile) != (size_t)userCount) {
            printf("Error: Failed to write bills data to file.\n");
            fclose(billsFile);
            return false;
        }
    }
    fclose(billsFile);
    
    printf("Data saved successfully to files.\n");
    return true;
}

bool loadDataFromFiles(void) {
    // Load users data
    if (!isFileExists(USERS_FILE) || !isFileExists(BILLS_FILE)) {
        printf("Data files not found. Starting with empty database.\n");
        userCount = 0;
        return true; // Not an error for first run
    }
    
    FILE* usersFile = openFile(USERS_FILE, "rb");
    if (!usersFile) {
        printf("Error: Unable to open users file for loading.\n");
        return false;
    }
    
    // Read user count
    if (fread(&userCount, sizeof(int), 1, usersFile) != 1) {
        printf("Error: Failed to read user count from file.\n");
        fclose(usersFile);
        return false;
    }
    
    // Validate user count
    if (userCount < 0 || userCount > MAX_USERS) {
        printf("Error: Invalid user count in file: %d\n", userCount);
        fclose(usersFile);
        userCount = 0;
        return false;
    }
    
    // Read all users
    if (userCount > 0) {
        if (fread(users, sizeof(UserInfo), (size_t)userCount, usersFile) != (size_t)userCount) {
            printf("Error: Failed to read users data from file.\n");
            fclose(usersFile);
            userCount = 0;
            return false;
        }
    }
    fclose(usersFile);
    
    // Load bills data
    FILE* billsFile = openFile(BILLS_FILE, "rb");
    if (!billsFile) {
        printf("Error: Unable to open bills file for loading.\n");
        userCount = 0;
        return false;
    }
    
    // Read bills data
    if (userCount > 0) {
        if (fread(bills, sizeof(BillInfo), (size_t)userCount, billsFile) != (size_t)userCount) {
            printf("Error: Failed to read bills data from file.\n");
            fclose(billsFile);
            userCount = 0;
            return false;
        }
    }
    fclose(billsFile);
    
    printf("Data loaded successfully from files. Users loaded: %d\n", userCount);
    return true;
}
