#include "CarManager.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

void CarManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            cars.push_back(make_shared<Car>(Car::fromCSV(line)));
        }
    }
}

void CarManager::saveToFile(const string& filename) {
    ofstream file(filename);
    for (const auto& car : cars) {
        file << car->toCSV() << '\n';
    }
}

void CarManager::addCar() {
    string brand, color;
    double fuel;
    int doors, year;
    double price;

    cout << "\n--- Додавання нового авто ---\n";
    cout << "Марка: "; cin >> brand;
    cout << "Колір: "; cin >> color;
    cout << "Витрати бензину (л/100км): "; cin >> fuel;
    cout << "Кількість дверей: "; cin >> doors;
    cout << "Рік випуску: "; cin >> year;
    cout << "Ціна (грн): "; cin >> price;

    cars.push_back(make_shared<Car>(brand, color, fuel, doors, year, price));
    cout << "Авто додано.\n";
}

void CarManager::showAllCars() const {
    cout << "\n--- Всі автомобілі ---\n";
    for (const auto& car : cars) car->print();
}

void CarManager::findMostEconomicalCar() const {
    if (cars.empty()) {
        cout << "База порожня.\n";
        return;
    }

    auto best = min_element(cars.begin(), cars.end(), [](const auto& a, const auto& b) {
        return a->getFuelConsumption() < b->getFuelConsumption();
        });

    cout << "\nНайекономічніший автомобіль:\n";
    (*best)->print();
}

void CarManager::averagePriceInPeriod() const {
    int start, end;
    cout << "\nВведіть початковий рік: "; cin >> start;
    cout << "Введіть кінцевий рік: "; cin >> end;
    double sum = 0;
    int count = 0;

    for (const auto& car : cars) {
        if (car->getYear() >= start && car->getYear() <= end) {
            sum += car->getPrice();
            count++;
        }
    }

    if (count == 0)
        cout << "Немає авто у вказаному періоді.\n";
    else
        cout << "Середня ціна: " << (sum / count) << " грн\n";
}
void CarManager::editCar() {
    if (cars.empty()) {
        cout << "Список порожній.\n";
        return;
    }

    int index;
    showAllCars(); // показати всі
    cout << "\nВведіть індекс авто для редагування (0..." << cars.size() - 1 << "): ";
    cin >> index;

    if (index < 0 || index >= cars.size()) {
        cout << "Неправильний індекс.\n";
        return;
    }

    string brand, color;
    double fuel;
    int doors, year;
    double price;

    cout << "\n--- Редагування авто ---\n";
    cout << "Нова марка: "; cin >> brand;
    cout << "Новий колір: "; cin >> color;
    cout << "Нові витрати бензину: "; cin >> fuel;
    cout << "Нова кількість дверей: "; cin >> doors;
    cout << "Новий рік: "; cin >> year;
    cout << "Нова ціна: "; cin >> price;

    cars[index] = make_shared<Car>(brand, color, fuel, doors, year, price);
    cout << "Авто оновлено.\n";
}

void CarManager::deleteCar() {
    if (cars.empty()) {
        cout << "Список порожній.\n";
        return;
    }

    int index;
    showAllCars();
    cout << "\nВведіть індекс авто для видалення (0..." << cars.size() - 1 << "): ";
    cin >> index;

    if (index < 0 || index >= cars.size()) {
        cout << "Неправильний індекс.\n";
        return;
    }

    cars.erase(cars.begin() + index);
    cout << "Авто видалено.\n";
}
