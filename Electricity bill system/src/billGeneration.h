#ifndef BILL_GENERATION_H
#define BILL_GENERATION_H

double calculateCurrentMonthUsage(const std::string& serviceNumber, double newReading);
double calculateCurrentMonthCharges(double usage);
double calculateTotalBill(const std::string& serviceNumber, double currMonthCharge);
bool generateBill(const std::string& serviceNumber);

#endif // BILL_GENERATION_H