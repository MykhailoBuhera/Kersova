#include "CarManager.h"
#include "AuthManager.h"
#include <windows.h>
#include <iostream>
using namespace std;

void showAdminMenu(AuthManager& auth) {
    int choice;
    do {
        cout << "\n--- ���� ������������ ---\n";
        cout << "1. ������ �����������\n";
        cout << "2. �������� �����������\n";
        cout << "3. ����������� ��� ������������\n";
        cout << "4. ����� �� ��������� ����\n";
        cout << "��� ����: ";
        cin >> choice;

        switch (choice) {
        case 1: auth.addUser(); break;
        case 2: auth.deleteUser(); break;
        case 3: auth.listUsers(); break;
        case 4: cout << "����������...\n"; break;
        default: cout << "������� ����.\n"; break;
        }
    } while (choice != 4);
}

void showUserMenu(CarManager& manager) {
    int choice;
    do {
        cout << "\n--- ���� ---\n";
        cout << "1. ����������� �� ����\n";
        cout << "2. ������ ���� ����\n";
        cout << "3. ������ ������������� ����\n";
        cout << "4. ������� ���� � �����\n";
        cout << "5. �����\n";
        cout << "��� ����: ";
        cin >> choice;

        switch (choice) {
        case 1: manager.showAllCars(); break;
        case 2: manager.addCar(); break;
        case 3: manager.findMostEconomicalCar(); break;
        case 4: manager.averagePriceInPeriod(); break;
        case 5: manager.saveToFile("cars.csv"); cout << "���������. �� ���������!\n"; break;
        default: cout << "������� ����. ��������� ��.\n"; break;
        }
    } while (choice != 5);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    AuthManager auth;
    if (!auth.login()) {
        cout << "������ ����������. ���������� ��������.\n";
        return 0;
    }

    CarManager manager;
    manager.loadFromFile("cars.csv");

    // ���� ���� � �������� ��������� ����
    if (auth.isAdmin()) {
        showAdminMenu(auth);
    }

    showUserMenu(manager);
    return 0;
}
