#include "AdminMenu.h"
#include <iostream>
#include <vector>

AdminMenu::AdminMenu(Library &lib, LoginSystem &login)
    : library(lib), loginSystem(login) {}

void AdminMenu::showMenu()
{
    int choice;

    do
    {
        displayAdminMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            handleBookManagement();
            break;
        case 2:
            handleUserManagement();
            break;
        case 3:
            handleSearchBooks();
            break;
        case 4:
            library.displayAllBooks();
            break;
        case 5:
            library.displayAllUsers();
            break;
        case 6:
            handleLibraryStats();
            break;
        case 0:
            std::cout << "Logging out from admin panel..." << std::endl;
            loginSystem.logout();
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0 && loginSystem.isUserAdmin());
}

void AdminMenu::displayAdminMenu()
{
    std::cout << "\n=== ADMIN PANEL ===" << std::endl;
    std::cout << "Logged in as: " << loginSystem.getCurrentUsername() << std::endl;
    std::cout << "Logged in as user ID: " << loginSystem.getCurrentUserId() << std::endl;
    std::cout << "1. Book Management" << std::endl;
    std::cout << "2. User Management" << std::endl;
    std::cout << "3. Search Books" << std::endl;
    std::cout << "4. Display All Books" << std::endl;
    std::cout << "5. Display All Users" << std::endl;
    std::cout << "6. Library Statistics" << std::endl;
    std::cout << "0. Logout" << std::endl;
    std::cout << "Enter your choice: ";
}

void AdminMenu::handleBookManagement()
{
    int choice;

    do
    {
        std::cout << "\n=== BOOK MANAGEMENT ===" << std::endl;
        std::cout << "1. Add Book" << std::endl;
        std::cout << "2. Remove Book" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::string isbn, title, author, genre;
            int year;

            std::cout << "Enter ISBN: ";
            std::cin >> isbn;
            std::cout << "Enter Title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter Author: ";
            std::getline(std::cin, author);
            std::cout << "Enter Genre: ";
            std::getline(std::cin, genre);
            std::cout << "Enter Publication Year: ";
            std::cin >> year;

            library.addBook(isbn, title, author, genre, year);
            break;
        }

        case 2:
        {
            std::string isbn;
            std::cout << "Enter ISBN of book to remove: ";
            std::cin >> isbn;
            library.removeBook(isbn);
            break;
        }
        }
    } while (choice != 0);
}

void AdminMenu::handleUserManagement()
{
    int choice;

    do
    {
        std::cout << "\n=== USER MANAGEMENT ===" << std::endl;
        std::cout << "1. Add User" << std::endl;
        std::cout << "2. Remove User" << std::endl;
        std::cout << "3. View User Details" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::string userId, username, password, name, email;
            int adminChoice;

            std::cout << "Enter User ID (e.g., U003): ";
            std::cin >> userId;

            std::cout << "Enter Username (for login): ";
            std::cin >> username;

            if (loginSystem.usernameExists(username))
            {
                std::cout << "Username already exists! Choose a different username." << std::endl;
                break;
            }

            std::cout << "Enter Password: ";
            std::cin >> password;

            std::cout << "Enter Full Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Enter Email: ";
            std::getline(std::cin, email);

            std::cout << "Is this user an admin? (1=Yes, 0=No): ";
            std::cin >> adminChoice;
            bool isAdmin = (adminChoice == 1);

            if (library.addUser(userId, username, password, name, email, isAdmin))
            {
                std::cout << "User created successfully! They can now login with username: "
                          << username << std::endl;
            }
            break;
        }

        case 2:
        {
            std::string id;
            std::cout << "Enter User ID to remove: ";
            std::cin >> id;
            library.removeUser(id);
            break;
        }

        case 3:
        {
            std::string id;
            std::cout << "Enter User ID to view: ";
            std::cin >> id;
            library.displayUserInfo(id);
            break;
        }
        }
    } while (choice != 0);
}

void AdminMenu::handleSearchBooks()
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

void AdminMenu::handleLibraryStats()
{
    std::cout << "\n=== LIBRARY STATISTICS ===" << std::endl;
    std::cout << "Total Books: " << library.getTotalBooks() << std::endl;
    std::cout << "Available Books: " << library.getAvailableBooksCount() << std::endl;
    std::cout << "Total Users: " << library.getTotalUsers() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}
