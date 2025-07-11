#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>
#include <unordered_map>
using namespace std;

class AuthManager {
private:
    unordered_map< string, string> users;
    string currentUser;
    const string filename = "users.txt";
    int deleteAttempts = 0;


public:
    AuthManager();

    void loadUsers();
    void saveUsers();

    bool login();
    bool isAdmin() const;
    bool reauthenticate();
    string getCurrentUser() const;

    // admin-only
    void addUser();
    void deleteUser();
    void listUsers();
};

#endif
