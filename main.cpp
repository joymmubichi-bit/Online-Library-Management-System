#include "src/Library.h"
#include "src/Login.h"
#include "src/AdminMenu.h"
#include "src/UserMenu.h"
#include <iostream>

void displayMainMenu()
{
    std::cout << "\n=== ONLINE LIBRARY MANAGEMENT SYSTEM ===" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void loginMenu(Library &library, LoginSystem &loginSystem)
{
    std::string username, password;

    std::cout << "\n=== LOGIN ===" << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    if (loginSystem.login(username, password))
    {
        if (loginSystem.isUserAdmin())
        {
            AdminMenu adminMenu(library, loginSystem);
            adminMenu.showMenu();
        }
        else
        {
            UserMenu userMenu(library, loginSystem, loginSystem.getCurrentUserId());
            userMenu.showMenu();
        }
    }
}

int main()
{
    Library library;
    LoginSystem loginSystem(library);

    // Add Kenyan high school books and IT books
    library.addBook("978-9966-11-123-4", "Chozi la Heri", "Asumpta K Matei", "Literature", 1990);
    library.addBook("978-9966-11-234-5", "Weep Not, Child", "Ngugi wa Thiong'o", "Literature", 1964);
    library.addBook("978-9966-11-345-6", "Mathematics for Kenya Secondary", "M. Wanyoike", "Mathematics", 2015);
    library.addBook("978-9966-11-456-7", "Learning C++", "Purity Wanjala", "Programming", 2018);
    library.addBook("978-9966-11-567-8", "Introduction to Computer Science", "Lewis Kamau", "Programming", 2017);

    // Add initial users WITH USERNAMES AND PASSWORDS
    library.addUser("U001", "mwangi", "password123", "Mwangi", "mwangi@example.co.ke", false);
    library.addUser("U002", "ngugi", "password456", "Ngugi", "ngugi@example.co.ke", false);
    library.addUser("ADM001", "admin", "admin123", "System Administrator", "admin@library.co.ke", true);

    int choice;

    do
    {
        displayMainMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            loginMenu(library, loginSystem);
            break;
        case 2:
            std::cout << "Thank you for using the Library Management System!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (choice != 2);

    return 0;
}
