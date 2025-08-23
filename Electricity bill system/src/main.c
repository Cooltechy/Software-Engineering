#include "user_module.h"
#include "bill_generator.h"
#include "payment.h"
#include "report.h"

void displayMenu(void) {
    printf("\n=== ELECTRICITY BILL MANAGEMENT SYSTEM ===\n");
    printf("1. Register User\n");
    printf("2. Generate Bill\n");
    printf("3. Process Payment\n");
    printf("4. Report - Bills Not Paid\n");
    printf("5. Report - By Service Number\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main(void) {
    int choice;
    char name[MAX_NAME_LENGTH], phone[MAX_PHONE_LENGTH], address[MAX_ADDRESS_LENGTH];
    char serviceNumber[SERVICE_NUMBER_LENGTH];
    double reading, amount;
    
    // Load existing data from files
    printf("Loading existing data...\n");
    if (!loadDataFromFiles()) {
        printf("Warning: Failed to load existing data. Starting fresh.\n");
    }
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Phone: ");
                scanf("%s", phone);
                printf("Enter Address: ");
                scanf(" %[^\n]", address);
                
                if (registerUser(name, phone, address, serviceNumber)) {
                    printf("User registered successfully!\n");
                    printf("Your Service Number: %s\n", serviceNumber);
                    saveDataToFiles(); // Auto-save after registration
                } else {
                    printf("Registration failed! Maximum users reached.\n");
                }
                break;
                
            case 2:
                printf("Enter Service Number: ");
                scanf("%s", serviceNumber);
                
                // Validate user first before asking for meter reading
                if (!isUserValid(serviceNumber)) {
                    printf("Error: Invalid service number! User not found.\n");
                    break;
                }
                
                printf("User validated successfully!\n");
                printf("Enter Current Month Reading: ");
                scanf("%lf", &reading);
                
                if (generateBill(serviceNumber, reading)) {
                    printf("Bill generated successfully!\n");
                    reportByServiceNumber(serviceNumber);
                    saveDataToFiles(); // Auto-save after bill generation
                } else {
                    printf("Failed to generate bill! Error in calculation.\n");
                }
                break;
                
            case 3:
                printf("Enter Service Number: ");
                scanf("%s", serviceNumber);
                
                // Validate user first before asking for payment amount
                if (!isUserValid(serviceNumber)) {
                    printf("Error: Invalid service number! User not found.\n");
                    break;
                }
                
                printf("User validated successfully!\n");
                printf("Enter Payment Amount: ");
                scanf("%lf", &amount);
                
                PaymentStatus status = processPayment(serviceNumber, amount);
                if (status == PAYMENT_SUCCESS) {
                    printf("Payment processed successfully!\n");
                    saveDataToFiles(); // Auto-save after payment
                } else if (status == USER_NOT_FOUND) {
                    printf("Error: User not found!\n");
                } else {
                    printf("Payment failed!\n");
                }
                break;
                
            case 4:
                reportBillNotPaid();
                break;
                
            case 5:
                printf("Enter Service Number: ");
                scanf("%s", serviceNumber);
                reportByServiceNumber(serviceNumber);
                break;
                
            case 6:
                printf("Saving data before exit...\n");
                if (saveDataToFiles()) {
                    printf("Data saved successfully.\n");
                } else {
                    printf("Warning: Failed to save data.\n");
                }
                printf("Thank you for using Electricity Bill Management System!\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
