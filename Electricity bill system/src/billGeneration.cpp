#include "billGeneration.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "userModule.h"

bool generateBill(const std::string& serviceNumber){
    if(!isUserExist(serviceNumber)){
        std::cerr << "Error: User with this Service Number " << serviceNumber << " does not exist!\n";
        return false;       
    }

    double newReading = 0.0, oldReading = 0.0;
    bool readingFound = false;
    
    std::ifstream billFile("meter_readings.txt"); // Use different file for input
    if (!billFile) {
        std::cerr << "Error: Could not open meter_readings.txt for reading!\n";
        return false;
    }
    else{
        //prevMonthReading fetching out
        std::string line;
        while (std::getline(billFile, line)) {
            std::istringstream iss(line);
            std::string token;
            std::getline(iss, token, ','); // Service Number
            if (token == serviceNumber) {
                std::getline(iss, token, ','); // Current Month Reading
                newReading = std::stod(token);
                std::getline(iss, token, ','); // Previous Month Reading
                oldReading = std::stod(token);
                readingFound = true;
                break;
            }
        }
        billFile.close();
    }
    
    if (!readingFound) {
        std::cerr << "Error: No meter reading found for service number " << serviceNumber << "!\n";
        return false;
    }

    // Module Calling to perform certain task
    double currMonthUsage = calculateCurrentMonthUsage(serviceNumber, newReading);
    double currMonthCharge = calculateCurrentMonthCharges(currMonthUsage);
    double totalBill = calculateTotalBill(serviceNumber, currMonthCharge);

    // Save bill information to a file or database
    std::ofstream outputFile("generated_bills.txt", std::ios::app);
    if (!outputFile) {
        std::cerr << "Error: Could not open generated_bills.txt for writing!\n";
        return false;
    }
    
    outputFile << serviceNumber << "," << currMonthUsage << "," << currMonthCharge << "," << totalBill << "\n";
    outputFile.close();
    
    std::cout << "Bill generated successfully for service number: " << serviceNumber << std::endl;

    return true;
}