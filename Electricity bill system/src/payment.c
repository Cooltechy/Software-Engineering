#include "payment.h"
#include "user_module.h"

extern int findUserIndex(const char* serviceNumber);

void updateBillStatus(const char* serviceNumber, double amount) {
    int index = findUserIndex(serviceNumber);
    if (index == -1) return;
    
    bills[index].lastAmtPaid = amount;
    bills[index].dues = bills[index].totalAmount - bills[index].lastAmtPaid;
    bills[index].totalAmount = 0;
}

PaymentStatus processPayment(const char* serviceNumber, double amount) {
    if (!isUserValid(serviceNumber)) {
        return USER_NOT_FOUND;
    }
    
    updateBillStatus(serviceNumber, amount);
    return PAYMENT_SUCCESS;
}
