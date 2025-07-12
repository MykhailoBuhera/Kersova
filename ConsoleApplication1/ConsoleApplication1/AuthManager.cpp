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

    // ���� ���� ������� � ������ ���������� �����
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

    cout << "����: ";
    cin >> username;
    cout << "������: ";
    cin >> password;

    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        currentUser = username;
        return true;
    }
    else {
        cout << "������� ���� ��� ������.\n";
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
    cout << "����� ����: ";
    cin >> username;
    if (users.count(username)) {
        cout << "����� ���������� ��� ����.\n";
        return;
    }
    cout << "������: ";
    cin >> password;
    users[username] = password;
    saveUsers();
    cout << "����������� ������.\n";
}

void AuthManager::deleteUser() {
    string username;
    cout << "������ ���� ��� ���������: ";
    cin >> username;
    if (username == "admin") {
       // cout << "��������� �������� ������������.\n";
        //return;
        deleteAttempts += 1;
        if (deleteAttempts == 1)
        {
            cout << "��������� �������� ������������.\n";
            return;
        }
        if (deleteAttempts == 2 )
        {
            cout << "������� �� ������ �������� ����� ���� ���� ��������\n";
            return;
        }
        if (deleteAttempts == 3)
        {
            cout << "� � ������ ���������� ������ �������� � ��� �� �����\n";
            return;
        }
        if (deleteAttempts >= 4)
        {
            cout << " ³������� ����\n";
            return;
        }


    }
    if (users.erase(username)) {
        saveUsers();
        cout << "����������� ��������.\n";
    }
    else {
        cout << "����������� �� ��������.\n";
    }
}

void AuthManager::listUsers() {
    cout << "\n������ ������������:\n";
    for (const auto& pair : users) {
      cout << pair.first << ':' << pair.second << '\n';
    }

}
bool AuthManager::reauthenticate() {
    cout << "\n--- ���� ����������� ---\n";
    return login(); // ������ ������� login() �����
}

