#include "AuthManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace std;

AuthManager::AuthManager() : filename("users.txt"), deleteAttempts(0) {
    loadUsers();
}
// Constructor that takes a vector of users (expects "username:password" format)(параметризований)
AuthManager::AuthManager(const std::vector<std::string>& usersVec) {
    for (const auto& entry : usersVec) {
        auto pos = entry.find(':');
        if (pos != std::string::npos) {
            std::string username = entry.substr(0, pos);
            std::string password = entry.substr(pos + 1);
            users[username] = password;
        }
    }
    saveUsers();
}

// Copy constructor
AuthManager::AuthManager(const AuthManager& other)
    : filename(other.filename), users(other.users), currentUser(other.currentUser), deleteAttempts(other.deleteAttempts) {
}

// Move constructor
AuthManager::AuthManager(AuthManager&& other) noexcept
    : filename(std::move(other.filename)), users(std::move(other.users)), currentUser(std::move(other.currentUser)), deleteAttempts(other.deleteAttempts) {
}


// Destructor
AuthManager::~AuthManager() {
    saveUsers();
    cout << "аутменджер видалено\n";
}

void AuthManager::loadUsers() {
    try {
        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("Cannot open users.txt");
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string username, password;
            if (getline(iss, username, ':') && getline(iss, password)) {
                users[username] = password;
            }
        }
        file.close();

        // If file is empty, add default admin
        if (users.empty()) {
            users["admin"] = "admin123";
            saveUsers();
        }
    }
    catch (const exception& ex) {
        cerr << "Error loading users: " << ex.what() << endl;
        users.clear();
        users["admin"] = "admin123";
        saveUsers();
    }
}

void AuthManager::saveUsers() {
    try {
        ofstream file(filename);
        if (!file.is_open()) throw runtime_error("Cannot open users.txt for writing");
        for (const auto& pair : users) {
            file << pair.first << ':' << pair.second << '\n';
        }
        file.close();
    }
    catch (const exception& ex) {
        cerr << "Error saving users: " << ex.what() << endl;
    }
}

bool AuthManager::login() {
    try {
        if (users.empty()) throw runtime_error("users.txt is empty");
        if (users.count("admin") == 0)
            throw runtime_error("No admin user found");
    }
    catch (const exception& ex) {
        cerr << "Auth error: " << ex.what() << endl;
        return false;
    }

    string username, password;
    cout << "Логін: ";
    cin >> username;
    cout << "Пароль: ";
    cin >> password;

    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        currentUser = username;
        return true;
    }
    else {
        cout << "Невірний логін або пароль.\n";
        return false;
    }
}

bool AuthManager::isAdmin() const {
    return currentUser == "admin";
}

string AuthManager::getCurrentUser() const {
    return currentUser;
}

void AuthManager::addUser() {
    string username, password;
    cout << "Новий логін: ";
    cin >> username;
    if (users.count(username)) {
        cout << "Такий користувач вже існує.\n";
        return;
    }
    cout << "Пароль: ";
    cin >> password;
    users[username] = password;
    saveUsers();
    cout << "Користувача додано.\n";
}

void AuthManager::deleteUser() {
    string username;
    cout << "Введіть логін для видалення: ";
    cin >> username;
    if (username == "admin") {
        deleteAttempts += 1;
        switch (deleteAttempts) {
        case 1: cout << "Неможливо видалити адміністратора.\n"; return;
        case 2: cout << "Неможна це робити програма капут якщо адмін видалити\n"; return;
        case 3: cout << "Я ж сказав заборонено машина розумніша і знає як краще\n"; return;
        default: cout << "Відчепися глек\n"; return;
        }
    }
    if (users.erase(username)) {
        saveUsers();
        cout << "Користувача видалено.\n";
    }
    else {
        cout << "Користувача не знайдено.\n";
    }
}

void AuthManager::listUsers() {
    cout << "\nСписок користувачів:\n";
    for (const auto& pair : users) {
        cout << pair.first << ':' << pair.second << '\n';
    }
}

bool AuthManager::reauthenticate() {
    cout << "\n--- Зміна користувача ---\n";
    return login();
}

