# Hotel Management System (C++ / Qt)

## Overview
This project is a Hotel Management System implemented in C++ with a Qt-based GUI.  
It manages customers, rooms, reservations, and reviews using structs and arrays, with file handling used only for saving and loading data.

---

## Program Flow

When the program starts, the user chooses:

1. Customer  
2. Admin  

### Customer
- Logs in using username and password  
- After login, a list of available functions is displayed  

### Admin
- Logs in using admin credentials  
- After login, a list of available functions is displayed  

---

## Features

### Customer Functions
- Log in / Log out  
- View available rooms  
- Reserve a room  
- Edit reservation dates  
- Cancel reservation  
- Add room review  

### Admin Functions
- Log in / Log out  
- Add reservation for a customer  
- Edit reservation (change start/end dates if applicable)  
- Cancel reservation  
- View reviews:
  - All reviews  
  - Seen reviews  
  - Unseen reviews  
  - Reviews from the last 30 days  

---

## Data Structures

The system uses structs and arrays for:

- Customers  
- Rooms  
- Reviews  
- Admins  

All data is processed in memory during runtime.

---

## File Handling

Files are used only for:

1. Saving data before closing the program  
2. Loading data at program start  

Files used:
- `customers.txt`  
- `rooms.txt`  
- `reviews.txt`  

No data processing is performed directly on files.

---

## Minimum Requirements

- At least 5 predefined Customers  
- At least 50 Rooms (10 rooms per floor)  
- At least 5 predefined Reviews  
- At least 1 Admin account  

---

## Additional Features

- Graphical User Interface using Qt  
- Automatic calculation of:
  - Available rooms  
  - Reviews from the last 30 days  
- Input validation (email, password, credit card, etc.)  
- Basic password encryption  

---

## Build Requirements

- C++  
- Qt 6 (Core, GUI, Widgets)  
- CMake (version 3.16 or higher)  

---

## Notes

- All operations (search, edit, display) are performed using arrays and structs.  
- Files are strictly used for persistence only, as required.  
