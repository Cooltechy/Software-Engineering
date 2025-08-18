#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 10
#define MAX_ADDRESS_LENGTH 200
#define SERVICE_NUMBER_LENGTH 37
#define MAX_USERS 1000

typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char serviceNumber[SERVICE_NUMBER_LENGTH];
} UserInfo;

typedef struct {
    char serviceNumber[SERVICE_NUMBER_LENGTH];
    double currMonthReading;
    double prevMonthReading;
    double currMonthUsage;
    double dues;
    double currMonthBill;
    double totalAmount;
    double lastAmtPaid;
} BillInfo;

extern UserInfo users[MAX_USERS];
extern BillInfo bills[MAX_USERS];
extern int userCount;

#endif
