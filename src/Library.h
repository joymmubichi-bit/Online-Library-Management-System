// Library.h - Add login-related methods
#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include <vector>
#include <map>

class Library
{
private:
    std::map<std::string, Book *> books;
    std::map<std::string, User *> users; // Now stores User objects with credentials

public:
    Library();
    ~Library();

    // Book Management (unchanged)
    bool addBook(const std::string &ISBN, const std::string &title,
                 const std::string &author, const std::string &genre, int year);
    bool removeBook(const std::string &ISBN);
    Book *findBook(const std::string &ISBN) const;
    std::vector<Book *> searchBooks(const std::string &keyword) const;
    void displayAllBooks() const;

    // User Management - UPDATED TO INCLUDE USERNAME AND PASSWORD
    bool addUser(const std::string &userId, const std::string &username,
                 const std::string &password, const std::string &name,
                 const std::string &email, bool isAdmin = false);
    bool removeUser(const std::string &userId);
    User *findUser(const std::string &userId) const;
    User *findUserByUsername(const std::string &username) const;                           // NEW METHOD
    bool authenticateUser(const std::string &username, const std::string &password) const; // NEW METHOD
    void displayAllUsers() const;

    // Borrowing System
    bool borrowBook(const std::string &userId, const std::string &ISBN);
    bool returnBook(const std::string &userId, const std::string &ISBN);

    bool canUserBorrow(const std::string &userId, const std::string &ISBN) const;
    std::vector<Book *> getUserBorrowedBooks(const std::string &userId) const;
    void displayUserInfo(const std::string &userId) const;

    // Statistics
    int getTotalBooks() const;
    int getTotalUsers() const;
    int getAvailableBooksCount() const;
};

#endif
