#include "Login.h"
#include <iostream>

LoginSystem::LoginSystem(Library &lib)
    : library(lib), currentUserId(""), currentUsername(""), currentIsAdmin(false) {}

bool LoginSystem::login(const std::string &username, const std::string &password)
{
    // Use Library to authenticate
    User *user = library.findUserByUsername(username);

    if (!user)
    {
        std::cout << "User not found!" << std::endl;
        return false;
    }

    if (user->getPassword() != password)
    {
        std::cout << "Incorrect password!" << std::endl;
        return false;
    }

    currentUserId = user->getUserId();
    currentUsername = username;
    currentIsAdmin = user->getIsAdmin();

    std::cout << "Login successful! Welcome " << user->getName() << std::endl;
    return true;
}

void LoginSystem::logout()
{
    currentUserId = "";
    currentUsername = "";
    currentIsAdmin = false;
    std::cout << "Logged out successfully!" << std::endl;
}

bool LoginSystem::isLoggedIn() const
{
    return !currentUserId.empty();
}

bool LoginSystem::isUserAdmin() const
{
    return currentIsAdmin;
}

std::string LoginSystem::getCurrentUserId() const
{
    return currentUserId;
}

std::string LoginSystem::getCurrentUsername() const
{
    return currentUsername;
}

bool LoginSystem::usernameExists(const std::string &username) const
{
    return (library.findUserByUsername(username) != nullptr);
}
