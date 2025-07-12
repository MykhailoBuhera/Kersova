#include "CarManager.h"
#include "AuthManager.h"
#include <windows.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    AuthManager auth;
    CarManager manager;
    manager.loadFromFile("cars.csv");

    while (true) {
        if (!auth.login()) {
            cout << "Спроба входу неуспішна. Повторити? (1 - так, 0 - вихід): ";
            int retry; cin >> retry;
            if (retry != 1) break;
            continue;
        }

        bool activeSession = true;

        while (activeSession) {
            if (auth.isAdmin()) {
                system("cls");
                cout << "Вітаємо вас адміністраторе\n";
                cout << "\n--- Меню адміністратора ---\n";
                cout << "1. Додати користувача\n";
                cout << "2. Видалити користувача\n";
                cout << "3. Переглянути всіх користувачів\n";
                cout << "4. Перейти до меню авто\n";
                cout << "5. Змінити користувача\n";
                cout << "6. Вийти з програми\n";
                cout << "Ваш вибір: ";
                int choice;
                cin >> choice;

                switch (choice) {
                case 1: auth.addUser(); break;
                case 2: auth.deleteUser(); break;
                case 3: auth.listUsers(); break;
                case 4: goto car_menu;
                case 5: activeSession = false; break; // змінити користувача
                case 6: manager.saveToFile("cars.csv"); return 0;
                default: cout << "Невірний вибір.\n"; break;
                }
            }
            else {
            car_menu:
                cout << "1. Переглянути всі авто\n";
                cout << "2. Додати нове авто\n";
                cout << "3. Найекономічніше авто\n";
                cout << "4. Середня ціна у періоді\n";
                cout << "5. Редагувати авто\n";         
                cout << "6. Видалити авто\n";           
                cout << "7. Змінити користувача\n";
                cout << "8. Пошук авто за критеріями\n";
                cout << "9. Сортувати за ціною (зростання)\n";
                cout << "10. Сортувати за ціною (спадання)\n";
                cout << "11. Сортувати за роком (зростання)\n";
                cout << "12. Сортувати за роком (спадання)\n";
                cout << "13. Вийти з програми\n";
                cout << "Ваш вибір: ";
                int choice;
                cin >> choice;

            
                switch (choice) {
                    case 1: manager.showAllCars(); break;
                    case 2: manager.addCar(); break;
                    case 3: manager.findMostEconomicalCar(); break;
                    case 4: manager.averagePriceInPeriod(); break;
                    case 5: manager.editCar(); break;  
                    case 6: manager.deleteCar(); break;   
                    case 7: activeSession = false; break;
                    case 8: manager.searchCars(); break;
                    case 9: manager.sortByPrice(true); break;
                    case 10: manager.sortByPrice(false); break;
                    case 11: manager.sortByYear(true); break;
                    case 12: manager.sortByYear(false); break;
                    case 13: manager.saveToFile("cars.csv"); return 0;

                    default: cout << "Невірний вибір.\n"; break;
                } 
            }
        }
    }

    return 0;
}
