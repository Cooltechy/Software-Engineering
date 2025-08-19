#include "userModule.h"
#include <iostream>
#include <fstream>
#include <uuid/uuid.h>
#include <algorithm>


// Function to get user information
UserInfo getUserInfo() {
    UserInfo user;
    std::cout << "Enter name: ";
    std::getline(std::cin, user.name);
    std::cout << "Enter phone number: ";
    std::getline(std::cin, user.phone);

    while (user.phone.length() != 10 || !std::all_of(user.phone.begin(), user.phone.end(), ::isdigit)) {
        std::cout << "Invalid phone number! Please enter a valid 10-digit phone number: ";
        std::getline(std::cin, user.phone);
    }

    std::cout << "Enter address: ";
    std::cin.ignore();  // Clear the newline character from the input buffer
    std::getline(std::cin, user.address);
    user.serviceNumber = getServiceNumber();
    return user;
}


//Generating unique service nuber
std::string getServiceNumber() {
    uuid_t uuid;
    char uuid_str[37];  // UUID strings are 36 chars + null terminator
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    return std::string(uuid_str);
}

// Check if user already exists
bool isUserExist(const std::string &serviceNumber) {
    std::ifstream userFile("users.txt");
    std::string line;
    while (std::getline(userFile, line)) {
        if (line.find(serviceNumber) != std::string::npos) {
            return true;
        }
    }
    return false;
}

//initialise new connection
void initialiseUserBill(const std::string &serviceNumber) {

    BillInfo bill;
    bill.serviceNumber = serviceNumber;
    bill.currMonthReading = 0.0;
    bill.prevMonthReading = 0.0;
    bill.currMonthUsage = 0.0;
    bill.dues = 0.0;
    bill.currMonthBill = 0.0;
    bill.totalAmount = 0.0;
    bill.lastAmtPaid = 0.0;

    std::ofstream billFile("_bill.txt" , std::ios::app);
    if(billFile) {
        billFile << bill.serviceNumber << ","
                  << bill.currMonthReading << ","
                  << bill.prevMonthReading << ","
                  << bill.currMonthUsage << ","
                  << bill.dues << ","
                  << bill.currMonthBill << ","
                  << bill.totalAmount << ","
                  << bill.lastAmtPaid << "\n";
        billFile.close();
    }
}

//registering user
bool registerUser(UserInfo &user) {
    user = getUserInfo();
    
    // Save user information to a file or database
    std::ofstream userFile("users.txt", std::ios::app);
    if (userFile) {
        userFile << user.name << "," << user.phone << "," << user.address << "," << user.serviceNumber << "\n";
        userFile.close();
        return true;
    }
    return false;
}