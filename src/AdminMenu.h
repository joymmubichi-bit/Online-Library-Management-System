#ifndef ADMINMENU_H
#define ADMINMENU_H

#include "Library.h"
#include "Login.h"

class AdminMenu
{
private:
    Library &library;
    LoginSystem &loginSystem;

public:
    AdminMenu(Library &lib, LoginSystem &login);
    void showMenu();

private:
    void displayAdminMenu();
    void handleBookManagement();
    void handleUserManagement();
    void handleSearchBooks();
    void handleDisplayAll();
    void handleLibraryStats();
};

#endif
