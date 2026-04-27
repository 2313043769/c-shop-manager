

# C++-based small store management system

## Introduction

This is a console-based inventory management system developed in C++. The system integrates core functional modules such as employee management, supplier management, product management, inventory monitoring, transaction records, and financial statistics. It stores data in plain text CSV format, without relying on a database, and can be used immediately upon opening.

## Functional Features

### User Authentication
- Administrator/employee login and logout
- Initialize the default administrator account

### Employee Management
- Addition, modification, deletion, and query of employee information
- ID number uniqueness verification
- Persistence of data in CSV format

### Supplier Management
- Addition, modification, deletion, and query of supplier information
- Supplier ID is automatically incremented

### Product Management
- Addition, modification, deletion, and query of product information
- Product-related supplier ID

### Inventory management
- Increase or decrease in inventory quantity
- Alarm threshold setting
- Automatic reminder for insufficient inventory

### Transaction Record
- Purchase/sales transaction records
- Query transactions by product/employee
- Calculate the total sales amount and total purchase amount

### Employee Work Record
- Record employees' working hours
- Calculate the total working hours

### Financial management
- Income and expenditure records
- Employee salary statistics
- Profit calculation

## Technology stack

| Category | Description |
|------|------|
| Programming Language | C++ (C++11 and above) |
| Core Libraries | C++ Standard Library (iostream/fstream/vector/map/ctime, etc.) |
| Data storage | Plain text file (CSV format) |
| System Dependency | Windows API (windows.h) |

## Compilation Environment

- **Compilers**: MinGW-w64 / MSVC / Dev-C++ / Code::Blocks
- **Operating System**: Windows 7/10/11 (32/64-bit)

## Quick Start

### Compile

Compile using g++:
```bash
g++ -std=c++11 manager1.cpp -o InventorySystem
```

Compile using MSVC:
```bash
cl /EHsc /std:c++11 manager1.cpp
```

### Run

Simply execute the compiled `InventorySystem.exe` file, and the program will automatically detect and create the required text data files during runtime.

## File Structure

### Source code
- `manager1.cpp` - Core source code, encompassing all class definitions and business logic

### Data storage file
After the program runs, the following files will be automatically generated:

| File Name | Purpose |
|--------|------|
| employee.txt | Employee information |
| supplier.txt | Supplier information |
| goodsinfo.txt | Product information |
| inventory.txt | Inventory information |
| transactions.txt | Transaction records |
| workrecords.txt | Employee work records |
| financial.txt | Financial data |

## Core class architecture

```
Date - Date processing (parsing, formatting, comparison, validity verification)
User / UserManager - User Authentication and Role Management
Employee / EmployeeManager - CRUD operations for employee information
Supplier / SupplierManager - CRUD operations for supplier information
Goods / GoodsManager - CRUD operations for goods information
Inventory / InventoryManager - Inventory quantity management and alarm
Transaction / TransactionManager - Transaction management
WorkRecord / WorkRecordManager - Employee work records and time calculation
FinancialManager - Financial statistics management
ShopManagementSystem - System main entry and interface interaction
```

### Utility classes

| Class Name | Function |
|------|------|
| FileHelper | File reading, writing, and existence verification |
| StringHelper | String splitting, trimming, converting to uppercase |

## Default Account

| Item | Value |
|------|-----|
| Username | admin |
| Password | admin123 |
| Role | Administrator (MANAGER) |

## Precautions

1. **System Compatibility**: This system only supports the Windows operating system
2. **Date format**: The format `YYYY-MM-DD` should be uniformly used. Dates not in this format will be deemed invalid
3. **Data Security**: Data is stored in plain text format. Please do not manually modify the file format
4. **Password Security**: Passwords are stored in plaintext. It is recommended to add encryption logic in production environments
5. **Working hours**: Working hours are calculated in a simplified manner (on a daily basis, with a default of 8 hours per day)

## Project Agreement

This project follows an open-source license and welcomes learning, discussion, and usage.
