#ifndef PAYMENT_H
#define PAYMENT_H

#include "types.h"

typedef enum {
    PAYMENT_SUCCESS,
    PAYMENT_FAILED,
    USER_NOT_FOUND
} PaymentStatus;

// Function prototypes
PaymentStatus processPayment(const char* serviceNumber, double amount);
void updateBillStatus(const char* serviceNumber, double amount);

#endif
