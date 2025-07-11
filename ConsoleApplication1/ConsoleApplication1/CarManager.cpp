#include "CarManager.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>// for lower
using namespace std;

string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return tolower(c); });
    return result;
}
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

    cout << "\n--- ��������� ������ ���� ---\n";
    cout << "�����: "; cin >> brand;
    cout << "����: "; cin >> color;
    cout << "������� ������� (�/100��): "; cin >> fuel;
    cout << "ʳ������ ������: "; cin >> doors;
    cout << "г� �������: "; cin >> year;
    cout << "ֳ�� (���): "; cin >> price;

    cars.push_back(make_shared<Car>(brand, color, fuel, doors, year, price));
    cout << "���� ������.\n";
}

void CarManager::showAllCars() const {
    cout << "\n--- �� �������� ---\n";
    for (const auto& car : cars) car->print();
}

void CarManager::findMostEconomicalCar() const {
    if (cars.empty()) {
        cout << "���� �������.\n";
        return;
    }

    auto best = min_element(cars.begin(), cars.end(), [](const auto& a, const auto& b) {
        return a->getFuelConsumption() < b->getFuelConsumption();
        });

    cout << "\n�������������� ���������:\n";
    (*best)->print();
}

void CarManager::averagePriceInPeriod() const {
    int start, end;
    cout << "\n������ ���������� ��: "; cin >> start;
    cout << "������ ������� ��: "; cin >> end;
    double sum = 0;
    int count = 0;

    for (const auto& car : cars) {
        if (car->getYear() >= start && car->getYear() <= end) {
            sum += car->getPrice();
            count++;
        }
    }

    if (count == 0)
        cout << "���� ���� � ��������� �����.\n";
    else
        cout << "������� ����: " << (sum / count) << " ���\n";
}
void CarManager::editCar() {
    if (cars.empty()) {
        cout << "������ �������.\n";
        return;
    }

    int index;
    showAllCars(); // �������� ��
    cout << "\n������ ������ ���� ��� ����������� (0..." << cars.size() - 1 << "): ";
    cin >> index;

    if (index < 0 || index >= cars.size()) {
        cout << "������������ ������.\n";
        return;
    }

    string brand, color;
    double fuel;
    int doors, year;
    double price;

    cout << "\n--- ����������� ���� ---\n";
    cout << "���� �����: "; cin >> brand;
    cout << "����� ����: "; cin >> color;
    cout << "��� ������� �������: "; cin >> fuel;
    cout << "���� ������� ������: "; cin >> doors;
    cout << "����� ��: "; cin >> year;
    cout << "���� ����: "; cin >> price;

    cars[index] = make_shared<Car>(brand, color, fuel, doors, year, price);
    cout << "���� ��������.\n";
}

void CarManager::deleteCar() {
    if (cars.empty()) {
        cout << "������ �������.\n";
        return;
    }

    int index;
    showAllCars();
    cout << "\n������ ������ ���� ��� ��������� (0..." << cars.size() - 1 << "): ";
    cin >> index;

    if (index < 0 || index >= cars.size()) {
        cout << "������������ ������.\n";
        return;
    }

    cars.erase(cars.begin() + index);
    cout << "���� ��������.\n";
}
void CarManager::searchCars() const {
    if (cars.empty()) {
        cout << "���� �������.\n";
        return;
    }

    string brandFilter, colorFilter;
    int yearFilter = 0;

    cout << "\n--- ����� ���� ---\n";
    cout << "������ ����� (��� ������� �������): ";
    cin.ignore();
    getline(cin, brandFilter);

    cout << "������ ���� (��� ������� �������): ";
    getline(cin, colorFilter);

    cout << "������ �� (��� 0 ��� ��������): ";
    cin >> yearFilter;

    // ��������� ������� �� �������� �������
    brandFilter = toLower(brandFilter);
    colorFilter = toLower(colorFilter);

    bool found = false;
    for (const auto& car : cars) {
        string carStr = toLower(car->toCSV());
        bool matches = true;

        if (!brandFilter.empty() && carStr.find(brandFilter) == string::npos)
            matches = false;
        if (!colorFilter.empty() && carStr.find(colorFilter) == string::npos)
            matches = false;
        if (yearFilter != 0 && car->getYear() != yearFilter)
            matches = false;

        if (matches) {
            car->print();
            found = true;
        }
    }

    if (!found)
        cout << "ͳ���� �� �������� �� �������� ���������.\n";
}

