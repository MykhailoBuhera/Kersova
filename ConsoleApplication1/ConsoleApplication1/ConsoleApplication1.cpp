#include "CarManager.h"
#include "AuthManager.h"
#include <windows.h>
#include <iostream>
using namespace std;
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    AuthManager auth;
    CarManager manager;
    manager.loadFromFile("cars.csv");

    while (true) {
        if (!auth.login()) {
            cout << "������ ����� ��������. ���������? (1 - ���, 0 - �����): ";
            int retry; cin >> retry;
            if (retry != 1) break;
            continue;
        }

        bool activeSession = true;

        while (activeSession) {
            if (auth.isAdmin()) {
                cout << "\n--- ���� ������������ ---\n";
                cout << "1. ������ �����������\n";
                cout << "2. �������� �����������\n";
                cout << "3. ����������� ��� ������������\n";
                cout << "4. ������� �� ���� ����\n";
                cout << "5. ������ �����������\n";
                cout << "6. ����� � ��������\n";
                cout << "��� ����: ";
                int choice;
                cin >> choice;

                switch (choice) {
                case 1: auth.addUser(); break;
                case 2: auth.deleteUser(); break;
                case 3: auth.listUsers(); break;
                case 4: goto car_menu; // ���, �� ��������� ���
                case 5: activeSession = false; break; // ������ �����������
                case 6: manager.saveToFile("cars.csv"); return 0;
                default: cout << "������� ����.\n"; break;
                }
            }
            else {
            car_menu:
                cout << "\n--- ���� ���� ---\n";
                cout << "1. ����������� �� ����\n";
                cout << "2. ������ ���� ����\n";
                cout << "3. ������������� ����\n";
                cout << "4. ������� ���� �� �����\n";
                cout << "5. ������ �����������\n";
                cout << "6. ����� � ��������\n";
                cout << "��� ����: ";
                int choice;
                cin >> choice;

                switch (choice) {
                case 1: manager.showAllCars(); break;
                case 2: manager.addCar(); break;
                case 3: manager.findMostEconomicalCar(); break;
                case 4: manager.averagePriceInPeriod(); break;
                case 5: activeSession = false; break;
                case 6: manager.saveToFile("cars.csv"); return 0;
                default: cout << "������� ����.\n"; break;
                }
            }
        }
    }

    return 0;
}
