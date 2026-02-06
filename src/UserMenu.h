#ifndef USERMENU_H
#define USERMENU_H

#include "Library.h"
#include "Login.h"
#include <string>

class UserMenu
{
private:
    Library &library;
    LoginSystem &loginSystem;
    std::string userId;

public:
    UserMenu(Library &lib, LoginSystem &login, const std::string &uid);
    void showMenu();

private:
    void displayUserMenu();
    void handleBorrowBook();
    void handleReturnBook();
    void handleSearchBooks();
    void handleViewProfile();
    void handleViewAvailableBooks();
};

#endif