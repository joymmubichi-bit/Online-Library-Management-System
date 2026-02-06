// User.cpp - Updated constructor and methods
#include "User.h"
#include <iostream>
#include <algorithm>

// Updated constructor
User::User(std::string id, std::string username, std::string password,
           std::string name, std::string email, bool admin, int maxBooks)
    : userId(id), username(username), password(password),
      name(name), email(email), maxBooksAllowed(maxBooks), isAdmin(admin) {}

// Getters
std::string User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
bool User::getIsAdmin() const { return isAdmin; }
std::vector<std::string> User::getBorrowedBooks() const { return borrowedBooks; }
int User::getMaxBooksAllowed() const { return maxBooksAllowed; }
int User::getBorrowedCount() const { return borrowedBooks.size(); }

// Setter for password
void User::setPassword(const std::string &newPassword) { password = newPassword; }

// ... rest of User.cpp remains the same

bool User::borrowBook(std::string ISBN)
{
    if (borrowedBooks.size() >= maxBooksAllowed)
    {
        std::cout << "Cannot borrow more books. Maximum limit reached." << std::endl;
        return false;
    }

    if (hasBook(ISBN))
    {
        std::cout << "You have already borrowed this book." << std::endl;
        return false;
    }

    borrowedBooks.push_back(ISBN);
    return true;
}

bool User::returnBook(std::string ISBN)
{
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), ISBN);

    if (it != borrowedBooks.end())
    {
        borrowedBooks.erase(it);
        return true;
    }

    std::cout << "This book was not borrowed by this user." << std::endl;
    return false;
}

bool User::hasBook(std::string ISBN) const
{
    return std::find(borrowedBooks.begin(), borrowedBooks.end(), ISBN) != borrowedBooks.end();
}

void User::displayInfo() const
{
    std::cout << "User ID: " << userId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Books Borrowed: " << borrowedBooks.size() << "/" << maxBooksAllowed << std::endl;

    if (!borrowedBooks.empty())
    {
        std::cout << "Borrowed Books ISBNs: ";
        for (const auto &isbn : borrowedBooks)
        {
            std::cout << isbn << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}
