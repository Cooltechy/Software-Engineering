#include "report.h"
#include "user_module.h"

void reportBillNotPaid(void) {
    printf("\n=== CUSTOMERS WITH UNPAID BILLS ===\n");
    printf("Criteria: Total Bill > 10000 OR Dues > 5000\n\n");
    
    bool found = false;
    for (int i = 0; i < userCount; i++) {
        if (bills[i].totalAmount > 10000 || bills[i].dues > 5000) {
            printf("Service Number: %s\n", users[i].serviceNumber);
            printf("Name: %s\n", users[i].name);
            printf("Phone: %s\n", users[i].phone);
            printf("Total Amount: %.2f\n", bills[i].totalAmount);
            printf("Dues: %.2f\n", bills[i].dues);
            printf("-------------------------\n");
            found = true;
        }
    }
    
    if (!found) {
        printf("No customers found with unpaid bills meeting the criteria.\n");
    }
}

void reportByServiceNumber(const char* serviceNumber) {
    if (!isUserValid(serviceNumber)) {
        printf("Error: User not found!\n");
        return;
    }
    
    int index = findUserIndex(serviceNumber);
    if (index == -1) {
        printf("Error: Bill details not found!\n");
        return;
    }
    
    printf("\n=== BILL DETAILS ===\n");
    printf("Service Number: %s\n", bills[index].serviceNumber);
    printf("Current Month Reading: %.2f\n", bills[index].currMonthReading);
    printf("Previous Month Reading: %.2f\n", bills[index].prevMonthReading);
    printf("Current Month Usage: %.2f\n", bills[index].currMonthUsage);
    printf("Current Month Bill: %.2f\n", bills[index].currMonthBill);
    printf("Dues: %.2f\n", bills[index].dues);
    printf("Total Amount: %.2f\n", bills[index].totalAmount);
    printf("Last Amount Paid: %.2f\n", bills[index].lastAmtPaid);
    printf("==================\n");
}
