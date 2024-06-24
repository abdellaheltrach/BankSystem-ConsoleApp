# BankSystem-ConsoleApp
A comprehensive Bank Management System built using C++ as a result of my learning journey. This project features account management, transaction processing, and customer service functionalities, showcasing object-oriented programming and efficient data handling techniques.

This project is a console-based bank management system implemented in C++. It allows users and clients to perform various banking operations, such as creating accounts, depositing funds, withdrawing funds, transferring funds, and checking account balances. The system distinguishes between users (bank employees with administrative privileges) and clients (regular bank customers).

## Features

- **User Management:** Users can create, update, delete client accounts, view transaction history, and perform administrative tasks.
- **Client Operations:** Clients can create accounts, deposit/withdraw funds, transfer funds, view account details, and check transaction history.
- **Transaction History:** All transactions are logged for tracking financial activities, including details like amounts, timestamps, and involved accounts.
- **Menu-Driven Interface:** Role-based menu options streamline the banking experience.
- **Currency Conversion:** Supports currency conversion for fund transfers between accounts in different currencies.

## Usage

1. **Compile:** Compile the source code using a C++ compiler (e.g., g++).
2. **Run:** Execute the compiled program to launch the bank management system.
3. **Login:** Users must log in with credentials (e.g., UserName: User1, Password: 1234).
4. **Menu Options:**
    - **Users (Administrators):** Create, update, delete client accounts, view transaction history, perform administrative tasks.
    - **Clients:** Create accounts, deposit/withdraw funds, transfer funds, view account details and transaction history.
5. **Logout:** Users can securely end their session.

## Technologies Used

- C++ programming language
- Standard C++ libraries for input/output and data manipulation

## Requirements

- C++ compiler (e.g., g++)
- Terminal or command prompt for running the compiled program

## Project Structure

- `BankSystem.cpp:` Main source code for the bank management system.
- `clsUser.h, User.cpp:` User class implementation for authentication, authorization, and administrative functions.
- `clsClient.h, Client.cpp:` Client class implementation for banking operations.
- `clsBankSystem.h, BankSystem.cpp:` Main logic and menu-driven interface.

## Contributing

Contributions are welcome! Feel free to provide feedback, suggest new features, or submit pull requests. Contact us at [abdellah.eltrach@gmail.com](mailto:abdellah.eltrach@gmail.com).


