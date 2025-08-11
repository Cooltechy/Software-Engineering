#include "bill_generator.h"
#include "user_module.h"

double calculateCurrentMonthUsage(const char* serviceNumber, double newReading) {
    int index = findUserIndex(serviceNumber);
    if (index == -1) return -1;
    
    bills[index].prevMonthReading = bills[index].currMonthReading;
    bills[index].currMonthReading = newReading;
    bills[index].currMonthUsage = bills[index].currMonthReading - bills[index].prevMonthReading;
    
    return bills[index].currMonthUsage;
}

double calculateCurrentMonthCharges(double usage) {
    double charge = 0.0;
    
    if (usage > 200) {
        if (usage > 800) {
            charge += (usage - 800) * 10.0 + 10;
            usage = 800;
        }
        if (usage > 400) {
            charge += (usage - 400) * 9.50 + 10;
            usage = 400;
        }
        if (usage > 300) {
            charge += (usage - 300) * 9.00 + 10;
            usage = 300;
        }
        if (usage > 200) {
            charge += (usage - 200) * 7.70 + 10;
            usage = 200;
        }
        charge += usage * 5.10 + 10;
        return charge;
    } else if (usage > 100) {
        if (usage > 100) {
            charge += (usage - 100) * 4.80 + 10;
            usage = 100;
        }
        charge += usage * 3.40 + 10;
        return charge;
    } else {
        if (usage > 50) {
            charge += (usage - 50) * 3.10 + 10;
            usage = 50;
        }
        charge += usage * 1.96 + 10;
        return charge;
    }
    return charge;
}

double calculateTotalBill(const char* serviceNumber, double currMonthCharge) {
    int index = findUserIndex(serviceNumber);
    if (index == -1) return -1;
    
    bills[index].currMonthBill = currMonthCharge;
    if (bills[index].totalAmount > 0) {
        bills[index].dues = bills[index].totalAmount;
    }
    bills[index].totalAmount = bills[index].dues + currMonthCharge;
    
    return bills[index].totalAmount;
}

bool generateBill(const char* serviceNumber, double newReading) {
    if (!isUserValid(serviceNumber)) {
        return false;
    }
    
    double usage = calculateCurrentMonthUsage(serviceNumber, newReading);
    if (usage < 0) return false;
    
    double charges = calculateCurrentMonthCharges(usage);
    double totalBill = calculateTotalBill(serviceNumber, charges);
    
    return totalBill >= 0;
}
