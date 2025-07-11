#include "CarManager.h"
#include "AuthManager.h"
#include <windows.h>
#include <iostream>
using namespace std;

void showAdminMenu(AuthManager& auth) {
    int choice;
    do {
        cout << "\n--- Меню адміністратора ---\n";
        cout << "1. Додати користувача\n";
        cout << "2. Видалити користувача\n";
        cout << "3. Переглянути всіх користувачів\n";
        cout << "4. Вихід до головного меню\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1: auth.addUser(); break;
        case 2: auth.deleteUser(); break;
        case 3: auth.listUsers(); break;
        case 4: cout << "Повернення...\n"; break;
        default: cout << "Невірний вибір.\n"; break;
        }
    } while (choice != 4);
}

void showUserMenu(CarManager& manager) {
    int choice;
    do {
        cout << "\n--- Меню ---\n";
        cout << "1. Переглянути всі авто\n";
        cout << "2. Додати нове авто\n";
        cout << "3. Знайти найекономічніше авто\n";
        cout << "4. Середня ціна у періоді\n";
        cout << "5. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1: manager.showAllCars(); break;
        case 2: manager.addCar(); break;
        case 3: manager.findMostEconomicalCar(); break;
        case 4: manager.averagePriceInPeriod(); break;
        case 5: manager.saveToFile("cars.csv"); cout << "Збережено. До побачення!\n"; break;
        default: cout << "Невірний вибір. Спробуйте ще.\n"; break;
        }
    } while (choice != 5);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    AuthManager auth;
    if (!auth.login()) {
        cout << "Доступ заборонено. Завершення програми.\n";
        return 0;
    }

    CarManager manager;
    manager.loadFromFile("cars.csv");

    // Якщо адмін — показати додаткове меню
    if (auth.isAdmin()) {
        showAdminMenu(auth);
    }

    showUserMenu(manager);
    return 0;
}
