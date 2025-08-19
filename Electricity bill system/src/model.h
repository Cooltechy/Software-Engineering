#ifndef STRUCT_MODULE_H
#define STRUCT_MODULE_H

#include<string>


struct UserInfo {
    std::string name;
    std::string phone;
    std::string address;
    std::string serviceNumber;
};

struct BillInfo {
    std::string serviceNumber;
    double currMonthReading;
    double prevMonthReading;
    double currMonthUsage;
    double dues;
    double currMonthBill;
    double totalAmount;
    double lastAmtPaid;
};

#endif
