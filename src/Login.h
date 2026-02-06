#ifndef LOGIN_H
#define LOGIN_H

#include "Library.h"
#include <string>

class LoginSystem
{
private:
    Library &library; // Reference to library for authentication
    std::string currentUserId;
    std::string currentUsername;
    bool currentIsAdmin;

public:
    LoginSystem(Library &lib);

    bool login(const std::string &username, const std::string &password);
    void logout();
    bool isLoggedIn() const;
    bool isUserAdmin() const;
    std::string getCurrentUserId() const;
    std::string getCurrentUsername() const;

    // Helper method for admin to check if username exists
    bool usernameExists(const std::string &username) const;
};

#endif
