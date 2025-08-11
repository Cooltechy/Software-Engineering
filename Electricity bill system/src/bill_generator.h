#ifndef BILL_GENERATOR_H
#define BILL_GENERATOR_H

#include "types.h"

// Function prototypes
double calculateCurrentMonthUsage(const char* serviceNumber, double newReading);
double calculateCurrentMonthCharges(double usage);
double calculateTotalBill(const char* serviceNumber, double currMonthCharge);
bool generateBill(const char* serviceNumber, double newReading);

#endif
