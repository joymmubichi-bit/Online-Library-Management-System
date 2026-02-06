#include "UserMenu.h"
#include <iostream>
#include <vector>

UserMenu::UserMenu(Library &lib, LoginSystem &login, const std::string &uid)
    : library(lib), loginSystem(login), userId(uid) {}

void UserMenu::showMenu()
{
    int choice;

    do
    {
        displayUserMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            handleSearchBooks();
            break;
        case 2:
            handleViewAvailableBooks();
            break;
        case 3:
            handleBorrowBook();
            break;
        case 4:
            handleReturnBook();
            break;
        case 5:
            handleViewProfile();
            break;
        case 0:
            std::cout << "Logging out..." << std::endl;
            loginSystem.logout();
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0 && loginSystem.isLoggedIn() && !loginSystem.isUserAdmin());
}

void UserMenu::displayUserMenu()
{
    User *user = library.findUser(userId);
    std::string userName = user ? user->getName() : "User";

    std::cout << "\n=== USER PANEL ===" << std::endl;
    std::cout << "Welcome, " << userName << "!" << std::endl;
    std::cout << "Logged in as user ID: " << loginSystem.getCurrentUserId() << std::endl;
    std::cout << "1. Search Books" << std::endl;
    std::cout << "2. View Available Books" << std::endl;
    std::cout << "3. Borrow Book" << std::endl;
    std::cout << "4. Return Book" << std::endl;
    std::cout << "5. My Profile & Borrowed Books" << std::endl;
    std::cout << "0. Logout" << std::endl;
    std::cout << "Enter your choice: ";
}

void UserMenu::handleSearchBooks()
{
    std::string keyword;
    std::cout << "Enter search keyword (title, author, genre, ISBN): ";
    std::cin.ignore();
    std::getline(std::cin, keyword);

    std::vector<Book *> results = library.searchBooks(keyword);

    if (results.empty())
    {
        std::cout << "No books found matching \"" << keyword << "\"" << std::endl;
    }
    else
    {
        std::cout << "\n=== Search Results (" << results.size() << " books found) ===" << std::endl;
        for (Book *book : results)
        {
            book->displayInfo();
        }
    }
}

void UserMenu::handleViewAvailableBooks()
{
    std::cout << "\n=== AVAILABLE BOOKS ===" << std::endl;

    std::vector<Book *> allBooks = library.searchBooks("");

    int availableCount = 0;
    for (Book *book : allBooks)
    {
        if (book->getAvailability())
        {
            book->displayInfo();
            availableCount++;
        }
    }

    if (availableCount == 0)
    {
        std::cout << "No books available at the moment." << std::endl;
    }
    else
    {
        std::cout << "Total available books: " << availableCount << std::endl;
    }
}

void UserMenu::handleBorrowBook()
{
    std::string isbn;
    std::cout << "Enter ISBN of book to borrow: ";
    std::cin >> isbn;

    if (library.canUserBorrow(userId, isbn))
    {
        library.borrowBook(userId, isbn);
    }
    else
    {
        std::cout << "Cannot borrow this book. It might be unavailable or you've reached your borrowing limit." << std::endl;
    }
}

void UserMenu::handleReturnBook()
{
    std::string isbn;
    std::cout << "Enter ISBN of book to return: ";
    std::cin >> isbn;

    library.returnBook(userId, isbn);
}

void UserMenu::handleViewProfile()
{
    library.displayUserInfo(userId);

}
