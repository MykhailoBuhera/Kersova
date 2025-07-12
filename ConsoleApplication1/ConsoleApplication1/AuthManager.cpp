#include "AuthManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

AuthManager::AuthManager() {
    loadUsers();
}

void AuthManager::loadUsers() {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string username, password;
        if (getline(iss, username, ':') && getline(iss, password)) {
            users[username] = password;
        }
    }

    // Якщо файл порожній — додаємо дефолтного адміна
    if (users.empty()) {
        users["admin"] = "admin123";
        saveUsers();
    }
}

void AuthManager::saveUsers() {
    ofstream file(filename);
    for (const auto& pair : users) {
        file << pair.first << ':' << pair.second << '\n';
    }

}

bool AuthManager::login() {
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
       // cout << "Неможливо видалити адміністратора.\n";
        //return;
        deleteAttempts += 1;
        if (deleteAttempts == 1)
        {
            cout << "Неможливо видалити адміністратора.\n";
            return;
        }
        if (deleteAttempts == 2 )
        {
            cout << "Неможна це робити програма капут якщо адмін видалити\n";
            return;
        }
        if (deleteAttempts == 3)
        {
            cout << "Я ж сказав заборонено машина розумніша і знає як краше\n";
            return;
        }
        if (deleteAttempts >= 4)
        {
            cout << " Відчепися глек\n";
            return;
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
    return login(); // Просто викликає login() знову
}

