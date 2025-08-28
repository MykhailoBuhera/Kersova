#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class AuthManager {
private:
    std::string filename = "users.txt";
    std::unordered_map<std::string, std::string> users;
    std::string currentUser;
    int deleteAttempts = 0;


public:
    AuthManager();
    AuthManager(const std::vector<std::string>& users);
    AuthManager(const AuthManager& other);
    AuthManager(AuthManager&& other) noexcept;
    ~AuthManager();

    void loadUsers();
    void saveUsers();

    bool login();
    bool isAdmin() const;
    bool reauthenticate();
    std::string getCurrentUser() const;

    // admin-only
    void addUser();
    void deleteUser();
    void listUsers();
};