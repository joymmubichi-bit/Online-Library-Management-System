ONLINE LIBRARY MANAGEMENT SYSTEM DOCUMENTATION
1. Introduction
The Online Library Management System is a system developed using C++ and Object-Oriented Programming (OOP) . It is designed to manage library activities such as adding books, removing books, searching for books, and handling the borrowing and returning of books.
2. Objectives of the System
The objectives of this system are:
To develop a library management system using C++.
To manage books and users efficiently.
To implement login authentication for system access.
To borrow and return books.
3. System Overview
The system allows authorized users to access library services after successful login. Once logged in, the user can perform operations such as adding books, removing books, searching for books, borrowing books, and returning books.
4. System Design
4.1 Login Module
The login module controls access to the system by requiring a username and password before the user can use library functions.
Such as:
•	User enters username and password.
•	System verifies the credentials.
•	Access is granted if the login details are correct.
•	Access is denied if incorrect details are entered.
This ensures that only authorized users can access the system.
4.2 Book Class
The Book class represents a book in the library.
Attributes
Book ISBN
Title
Author
Year of Publishe
Availability status
Functions
Display book information
Borrow book
Return book
4.3 User Class
The User class represents a library user.
Attributes
User ID
User name
Password
Functions
Display user details
4.4 Library Class
The Library class manages all library operations.
Functions
Add book
Remove book
Search book
Borrow book
Return book
Display all books
5. OOP Concepts Used
Encapsulation: Data members are kept private and accessed through public methods.
Modularity: The system is divided into separate classes for better organization.
6. Test Cases
The system was tested using the following cases:
•	Successful login with correct credentials.
•	Failed login with incorrect credentials.
•	Adding a new book.
•	Searching for an existing book.
•	Borrowing an available book.
•	Attempting to borrow an unavailable book.
•	Returning a borrowed book.
•	Removing a book from the system.
7. How to Compile and Run the Program
Compile and run the code use the below commands on cmd or visual studio code terminal:

To compile in VS code use this command:
g++ -std=c++11 -Isrc -o library_system.exe main.cpp src/*.cpp
(after downloading MSYS2 x86_64-20251213.exe - this is a C/C++ compiler for vs code)

To run use this command:
.\library_system.exe

login for admin is:
username:admin
password:admin123

login for user(sample):
username: mwangi
password:password123

9. Conclusion
The Online Library Management System  demonstrates the implementation of Object-Oriented Programming concepts in C++. The addition of a login module improves system security by restricting access to authorized users. The system provides a simple and effective way of managing library operations while reinforcing OOP design principles.
