#include "Library.h"
#include <iostream>
#include <algorithm>

Library::Library() {}

Library::~Library()
{
    for (auto &pair : books)
    {
        delete pair.second;
    }
    for (auto &pair : users)
    {
        delete pair.second;
    }
}

bool Library::addBook(const std::string &ISBN, const std::string &title,
                      const std::string &author, const std::string &genre, int year)
{
    if (books.find(ISBN) != books.end())
    {
        std::cout << "Book with ISBN " << ISBN << " already exists." << std::endl;
        return false;
    }

    books[ISBN] = new Book(ISBN, title, author, genre, year);
    std::cout << "Book added successfully: " << title << std::endl;
    return true;
}

bool Library::removeBook(const std::string &ISBN)
{
    auto it = books.find(ISBN);
    if (it == books.end())
    {
        std::cout << "Book with ISBN " << ISBN << " not found." << std::endl;
        return false;
    }

    if (!it->second->getAvailability())
    {
        std::cout << "Cannot remove book. It is currently borrowed." << std::endl;
        return false;
    }

    delete it->second;
    books.erase(it);
    std::cout << "Book removed successfully." << std::endl;
    return true;
}

Book *Library::findBook(const std::string &ISBN) const
{
    auto it = books.find(ISBN);
    return (it != books.end()) ? it->second : nullptr;
}

std::vector<Book *> Library::searchBooks(const std::string &keyword) const
{
    std::vector<Book *> results;

    for (const auto &pair : books)
    {
        if (pair.second->matchesSearch(keyword))
        {
            results.push_back(pair.second);
        }
    }

    return results;
}

void Library::displayAllBooks() const
{
    std::cout << "\n=== All Books in Library ===" << std::endl;
    std::cout << "Total Books: " << books.size() << std::endl;
    std::cout << "Available Books: " << getAvailableBooksCount() << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    for (const auto &pair : books)
    {
        pair.second->displayInfo();
    }
}

bool Library::addUser(const std::string &userId, const std::string &username,
                      const std::string &password, const std::string &name,
                      const std::string &email, bool isAdmin)
{

    if (users.find(userId) != users.end())
    {
        std::cout << "User with ID " << userId << " already exists." << std::endl;
        return false;
    }

    for (const auto &pair : users)
    {
        if (pair.second->getUsername() == username)
        {
            std::cout << "Username '" << username << "' already exists." << std::endl;
            return false;
        }
    }

    users[userId] = new User(userId, username, password, name, email, isAdmin);
    std::cout << "User added successfully: " << name << " (Username: " << username << ")" << std::endl;
    return true;
}

User *Library::findUser(const std::string &userId) const
{
    auto it = users.find(userId);
    return (it != users.end()) ? it->second : nullptr;
}

User *Library::findUserByUsername(const std::string &username) const
{
    for (const auto &pair : users)
    {
        if (pair.second->getUsername() == username)
        {
            return pair.second;
        }
    }
    return nullptr;
}

bool Library::authenticateUser(const std::string &username, const std::string &password) const
{
    User *user = findUserByUsername(username);
    if (!user)
    {
        return false;
    }
    return (user->getPassword() == password);
}

bool Library::removeUser(const std::string &userId)
{
    auto it = users.find(userId);
    if (it == users.end())
    {
        std::cout << "User with ID " << userId << " not found." << std::endl;
        return false;
    }

    if (it->second->getBorrowedCount() > 0)
    {
        std::cout << "Cannot remove user. They have " << it->second->getBorrowedCount()
                  << " borrowed book(s)." << std::endl;
        return false;
    }

    delete it->second;
    users.erase(it);
    std::cout << "User removed successfully. They can no longer login." << std::endl;
    return true;
}

void Library::displayAllUsers() const
{
    std::cout << "\n=== All Users in Library ===" << std::endl;
    std::cout << "Total Users: " << users.size() << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    for (const auto &pair : users)
    {
        pair.second->displayInfo();
    }
}

bool Library::borrowBook(const std::string &userId, const std::string &ISBN)
{
    User *user = findUser(userId);
    Book *book = findBook(ISBN);

    if (!user)
    {
        std::cout << "User not found." << std::endl;
        return false;
    }

    if (!book)
    {
        std::cout << "Book not found." << std::endl;
        return false;
    }

    if (!book->getAvailability())
    {
        std::cout << "Book is already borrowed by User ID: " << book->getBorrowedBy() << std::endl;
        return false;
    }

    if (user->borrowBook(ISBN))
    {
        book->setAvailability(false);
        book->setBorrowedBy(userId);
        std::cout << "Book borrowed successfully!" << std::endl;
        return true;
    }

    return false;
}

bool Library::returnBook(const std::string &userId, const std::string &ISBN)
{
    User *user = findUser(userId);
    Book *book = findBook(ISBN);

    if (!user)
    {
        std::cout << "User not found." << std::endl;
        return false;
    }

    if (!book)
    {
        std::cout << "Book not found." << std::endl;
        return false;
    }

    if (user->returnBook(ISBN))
    {
        book->setAvailability(true);
        book->setBorrowedBy("");
        std::cout << "Book returned successfully!" << std::endl;
        return true;
    }

    return false;
}

bool Library::canUserBorrow(const std::string &userId, const std::string &ISBN) const
{
    User *user = findUser(userId);
    Book *book = findBook(ISBN);

    if (!user || !book)
        return false;

    if (!book->getAvailability())
        return false;

    if (user->getBorrowedCount() >= user->getMaxBooksAllowed())
        return false;

    return true;
}

std::vector<Book *> Library::getUserBorrowedBooks(const std::string &userId) const
{
    std::vector<Book *> userBooks;
    User *user = findUser(userId);

    if (!user)
        return userBooks;

    std::vector<std::string> borrowedISBNs = user->getBorrowedBooks();

    for (const auto &isbn : borrowedISBNs)
    {
        Book *book = findBook(isbn);
        if (book)
        {
            userBooks.push_back(book);
        }
    }

    return userBooks;
}

void Library::displayUserInfo(const std::string &userId) const
{
    User *user = findUser(userId);
    if (!user)
    {
        std::cout << "User not found!" << std::endl;
        return;
    }

    user->displayInfo();

    std::vector<Book *> borrowedBooks = getUserBorrowedBooks(userId);
    if (!borrowedBooks.empty())
    {
        std::cout << "\n=== Currently Borrowed Books ===" << std::endl;
        for (Book *book : borrowedBooks)
        {
            book->displayInfo();
        }
    }
}

int Library::getTotalBooks() const
{
    return books.size();
}

int Library::getTotalUsers() const
{
    return users.size();
}

int Library::getAvailableBooksCount() const
{
    int count = 0;
    for (const auto &pair : books)
    {
        if (pair.second->getAvailability())
        {
            count++;
        }
    }
    return count;
}
