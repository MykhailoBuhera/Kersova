#include "CarManager.h"
#include "AuthManager.h"
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <limits> 
using namespace std;

int safeInput() {
    int value;
    while (true) {
        cin >> value;

        if (cin.fail()) {  // ���� ������� �� �����
            cin.clear(); // ������� ���� �������
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // ������� ����� �����
            cout << "�������: ������ �����! ��������� �� ���: ";
        }
        else {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // ������� "������" �����
            return value; // �������� �����
        }
    }
}



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    AuthManager auth;
    CarManager manager;
    manager.loadFromFile("cars.csv");

    while (true) {
        if (!auth.login()) {
            cout << "������ ����� ��������. ���������? (1 - ���, ,���� ���  ���� - �����): ";
            int retry; cin >> retry;
            if (retry != 1) break;
            continue;
        }
        bool activeSession = true;

        while (activeSession) {

            if (auth.isAdmin()) {
                cout << "\n³���� ���, ������������\n";
                cout << "\n--- ���� ������������ ---\n";
                cout << "1. ������ �����������\n";
                cout << "2. �������� �����������\n";
                cout << "3. ����������� ��� ������������\n";
                cout << "4. ������� �� ���� ����\n";
                cout << "5. ������ �����������\n";
                cout << "6. ����� � ��������\n";
                cout << "��� ����: ";
                int choice;
                choice = safeInput();

                switch (choice) {
                case 1: auth.addUser(); break;
                case 2: auth.deleteUser(); break;
                case 3: auth.listUsers(); break;
                case 4: {
                    bool carMenuActive = true;
                    while (carMenuActive) {
                        cout << "\n--- ���� ���� ---\n";
                        cout << "1. ����������� �� ����\n";
                        cout << "2. ������ ���� ����\n";
                        cout << "3. ������������� ����\n";
                        cout << "4. ������� ���� � �����\n";
                        cout << "5. ���������� ����\n";
                        cout << "6. �������� ����\n";
                        cout << "7. ����������� �� ���� ������������\n";
                        cout << "8. ����� ���� �� ��������� (searchCars)\n";
                        cout << "9. ����� �� ������ (findByBrand)\n";
                        cout << "10. ������ �� �������� ����\n";
                        cout << "11. ������ ����� ����\n";
                        cout << "12. ����������� ������ �� ����\n";
                        cout << "13. �������� �� ����\n";
                        cout << "14. ����������� ������� ������\n";
                        cout << "15. ��������� �� ����� (���������)\n";
                        cout << "16. ��������� �� ����� (��������)\n";
                        cout << "17. ��������� �� ����� (���������)\n";
                        cout << "18. ��������� �� ����� (��������)\n";
                        cout << "19. ��������� �� ��������� ��������\n";
                        cout << "20. Գ���� �� ��������\n";
                        cout << "21. Գ���� �� �����\n";
                        cout << "22. ��������\n";
                        cout << "23. ����� � ��������\n";
                        cout << "��� ����: ";
                        int carChoice;
                        carChoice = safeInput();

                        switch (carChoice) {
                        case 1: manager.showAllCars(); break;
                        case 2: manager.addCar(); break;
                        case 3: manager.findMostEconomicalCar(); break;
                        case 4: manager.averagePriceInPeriod(); break;
                        case 5: manager.editCar(); break;
                        case 6: manager.removeCar(); break;
                        case 7: carMenuActive = false; break;
                        case 8: manager.searchCars(); break;
                        case 9: manager.findByBrand(); break;
                        case 10: manager.findEconomicalCars(); break;
                        case 11: manager.findFamilyCars(); break;
                        case 12: manager.applyDiscountToCar(); break;
                        case 13: manager.showCarAge(); break;
                        case 14: manager.calcTripCost(); break;
                        case 15: manager.sortByPrice(true); break;
                        case 16: manager.sortByPrice(false); break;
                        case 17: manager.sortByYear(true); break;
                        case 18: manager.sortByYear(false); break;
                        case 19: manager.sortByFuelConsumption(true); break;
                        case 20: {
                            string color;
                            cout << "������ ����: "; cin >> color;
                            manager.filterByColor(color);
                            break;
                        }
                        case 21: {
                            int year;
                            cout << "������ ��: "; cin >> year;
                            manager.filterByYear(year);
                            break;
                        }
                        case 22: manager.showHelp(); break;
                        case 23: manager.saveToFile("cars.csv"); return 0;
                        default: cout << "������� ����.\n"; break;
                        }
                    }
                    break;
                }
                case 5: activeSession = false; break;
                case 6: manager.saveToFile("cars.csv"); return 0;
                default: cout << "������� ����.\n"; break;
                }
            }
            else {
                cout << "³����, " << auth.getCurrentUser() << "!\n";
                cout << "--- ���� ����������� ---\n";
                cout << "1. ����������� �� ����\n";
                cout << "2. ������������� ����\n";
                cout << "3. ������� ���� � �����\n";
                cout << "4. ����� ���� �� ��������� (searchCars)\n";
                cout << "5. ��������� �� ����� (���������)\n";
                cout << "6. ��������� �� ����� (��������)\n";
                cout << "7. ��������� �� ����� (���������)\n";
                cout << "8. ��������� �� ����� (��������)\n";
                cout << "9. Գ���� �� ��������\n";
                cout << "10. Գ���� �� �����\n";
                cout << "11. ��������\n";
                cout << "12. ����� � ��������\n";
                cout << "13. ������ �����������\n";
                cout << "��� ����: ";

                int choice;
                choice = safeInput();

                switch (choice) {
                case 1: manager.showAllCars(); break;
                case 2: manager.findMostEconomicalCar(); break;
                case 3: manager.averagePriceInPeriod(); break;
                case 4: manager.searchCars(); break;
                case 5: manager.sortByPrice(true); break;
                case 6: manager.sortByPrice(false); break;
                case 7: manager.sortByYear(true); break;
                case 8: manager.sortByYear(false); break;
                case 9: {
                    string color;
                    cout << "������ ����: "; cin >> color;
                    manager.filterByColor(color);
                    break;
                }
                case 10: {
                    int year;
                    cout << "������ ��: "; cin >> year;
                    manager.filterByYear(year);
                    break;
                }
                case 11: manager.showHelpnotadm(); break;
                case 12: manager.saveToFile("cars.csv"); return 0;
                case 13: activeSession = false; break;
                default: cout << "������� ����.\n"; break;
                }
            }
        }

    }

    return 0;
}
