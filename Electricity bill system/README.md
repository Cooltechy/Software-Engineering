# Electricity Bill Management System

A modular C implementation of an electricity bill management system with user registration, bill generation, payment processing, and reporting features.

## Features

- **User Management**: Register users with unique service numbers
- **Bill Generation**: Calculate bills based on tiered electricity rates
- **Payment Processing**: Handle payments and update bill status
- **Reporting**: Generate reports for unpaid bills and individual bill details

## Project Structure

```
Electricity bill system/
├── src/
│   ├── types.h           # Common data structures and constants
│   ├── user_module.h     # User management function prototypes
│   ├── user_module.c     # User registration and validation
│   ├── bill_generator.h  # Bill generation function prototypes
│   ├── bill_generator.c  # Bill calculation logic
│   ├── payment.h         # Payment processing prototypes
│   ├── payment.c         # Payment handling
│   ├── report.h          # Reporting function prototypes
│   ├── report.c          # Report generation
│   └── main.c            # Main program with menu interface
├── Makefile              # Build configuration
└── README.md             # This file
```

## Compilation and Usage

### Prerequisites
- GCC compiler
- Make utility

### Building the Project

```bash
cd "Electricity bill system"
make
```

### Running the Application

```bash
make run
```

Or directly:
```bash
./bin/electricity_bill
```

### Cleaning Build Files

```bash
make clean
```

## Usage

The application provides a menu-driven interface with the following options:

1. **Register User**: Register a new user with name, phone, and address
2. **Generate Bill**: Generate electricity bill for a service number
3. **Process Payment**: Process payment for a service number
4. **Report - Bills Not Paid**: Show customers with high unpaid bills
5. **Report - By Service Number**: Show detailed bill information
6. **Exit**: Exit the application

## Electricity Rate Slabs

The system uses tiered pricing for electricity consumption:

- 0-50 units: ₹1.96/unit + ₹10 fixed charge
- 51-100 units: ₹3.10/unit for excess + previous slab + ₹10
- 101-200 units: ₹4.80/unit for excess + previous slabs + ₹10
- 201-300 units: ₹5.10/unit for excess + previous slabs + ₹10
- 301-400 units: ₹7.70/unit for excess + previous slabs + ₹10
- 401-800 units: ₹9.00/unit for excess + previous slabs + ₹10
- 801+ units: ₹10.00/unit for excess + previous slabs + ₹10

## Module Description

### User Module
- Generates unique service numbers (UUID-like format)
- Registers new users with validation
- Initializes bill information for new users
- Validates existing service numbers

### Bill Generator
- Calculates current month usage based on meter readings
- Applies tiered pricing structure
- Manages dues and total bill amounts
- Updates bill status

### Payment Module
- Processes payments for service numbers
- Updates bill status after payment
- Handles payment validation

### Report Module
- Generates reports for unpaid bills (criteria: Total Bill > ₹10,000 OR Dues > ₹5,000)
- Displays detailed bill information by service number

## Data Structures

### UserInfo
- Name, Phone, Address
- Unique Service Number

### BillInfo
- Service Number reference
- Current/Previous month readings
- Usage calculations
- Bill amounts and payment history
