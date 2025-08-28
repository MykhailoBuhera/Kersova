#include "CarManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return tolower(c); });
    return result;
}

// ---------------- ��������� ���� ----------------
void CarManager::printCarIndexList() const {
    cout << "\n������\t�����\n";
    for (size_t i = 0; i < cars.size(); ++i) {
        cout << i << "\t";
        cars[i]->print();
    }
}

// ---------------- CRUD ----------------
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
    string brand, color, model;   
    double fuel, price;
    int doors, year;

    cout << "\n--- ��������� ������ ���� ---\n";
    cout << "�����: "; cin >> brand;
    cout << "������: "; cin >> model;             
    cout << "����: "; cin >> color;
    cout << "������� ������� (�/100��): "; cin >> fuel;
    cout << "ʳ������ ������: "; cin >> doors;
    cout << "г� �������: "; cin >> year;
    cout << "ֳ��: "; cin >> price;

    string packageName;
    bool hasAC, hasMultimedia, hasSafety;
    double configPrice;
    cin.ignore(); // ������� ����� ���� ������������ cin
    cout << "Package name: "; getline(cin, packageName);
    cout << "Has air conditioner (1/0): "; cin >> hasAC;
    cout << "Has multimedia (1/0): "; cin >> hasMultimedia;
    cout << "Has safety system (1/0): "; cin >> hasSafety;
    cout << "Configuration price: "; cin >> configPrice;

    Configuration config(brand, model, packageName, hasAC, hasMultimedia, hasSafety, configPrice);

    cars.push_back(make_shared<Car>(brand, color, model, fuel, doors, year, price, config));
    cout << "? ���� ������!\n";
}

void CarManager::showAllCars() const {
    if (cars.empty()) {
        cout << "���� �������.\n";
        return;
    }
    cout << "\n--- �� �������� ---\n";
    for (const auto& car : cars) car->print();
}

void CarManager::editCar() {
    int index;
    showAllCars();
    cout << "\n������ ������ ���� ��� �����������: ";
    cin >> index;

    if (index >= 0 && index < cars.size()) {
        string brand, color, model;
        double fuel, price;
        int doors, year;

        cout << "--- ����������� ���� ---\n";
        cout << "���� �����: "; cin >> brand;
        cout << "���� ������: "; cin >> model;      // <-- ����
        cout << "����� ����: "; cin >> color;
        cout << "��� ������� �������: "; cin >> fuel;
        cout << "���� ������� ������: "; cin >> doors;
        cout << "����� ��: "; cin >> year;
        cout << "���� ����: "; cin >> price;

		double configPrice;
        string packageName;
        bool hasAC, hasMultimedia, hasSafety;
        cin.ignore();
        cout << "Package name: "; getline(cin, packageName);
        cout << "Has air conditioner (1/0): "; cin >> hasAC;
        cout << "Has multimedia (1/0): "; cin >> hasMultimedia;
        cout << "Has safety system (1/0): "; cin >> hasSafety;
        cout << "Configuration price: "; cin >> configPrice;


        Configuration config(brand, model, packageName, hasAC, hasMultimedia, hasSafety, configPrice);
        Car car(brand, color, model, fuel, doors, year, price, config);


        cars[index] = make_shared<Car>(brand, color, model, fuel, doors, year, price, config);
        cout << "? ���� ��������!\n";
    }
    else {
        cout << "? ������� ������!\n";
    }
}

void CarManager::removeCar() {
    int index;
    showAllCars();
    cout << "\n������ ������ ���� ��� ���������: ";
    cin >> index;
    if (index >= 0 && index < cars.size()) {
        cars.erase(cars.begin() + index);
        cout << "? ���� ��������!\n";
    }
    else {
        cout << "? ������� ������!\n";
    }
}

// ---------------- �������� ----------------
void CarManager::findMostEconomicalCar() const {
    if (cars.empty()) {
        cout << "���� �������.\n"; return;
    }
    auto best = min_element(cars.begin(), cars.end(),
        [](auto& a, auto& b) { return a->getFuelConsumption() < b->getFuelConsumption(); });
    cout << "\n�������������� ���������:\n";
    (*best)->print();
}

void CarManager::averagePriceInPeriod() const {
    int start, end;
    cout << "\n������ ���������� ��: "; cin >> start;
    cout << "������ ������� ��: "; cin >> end;

    double sum = 0; int count = 0;
    for (const auto& car : cars) {
        if (car->getYear() >= start && car->getYear() <= end) {
            sum += car->getPrice();
            count++;
        }
    }
    if (count == 0) cout << "? ���� ���� � ����� �����.\n";
    else cout << "������� ����: " << sum / count << " ���\n";
}

// ---------------- ���������� ----------------
void CarManager::sortByPrice(bool ascending) {
    sort(cars.begin(), cars.end(), [ascending](auto& a, auto& b) {
        return ascending ? a->getPrice() < b->getPrice() : a->getPrice() > b->getPrice();
        });
    cout << "? ³���������� �� �����.\n";
}

void CarManager::sortByYear(bool ascending) {
    sort(cars.begin(), cars.end(), [ascending](auto& a, auto& b) {
        return ascending ? a->getYear() < b->getYear() : a->getYear() > b->getYear();
        });
    cout << "? ³���������� �� �����.\n";
}

void CarManager::sortByFuelConsumption(bool ascending) {
    sort(cars.begin(), cars.end(), [ascending](auto& a, auto& b) {
        return ascending ? a->getFuelConsumption() < b->getFuelConsumption()
            : a->getFuelConsumption() > b->getFuelConsumption();
        });
    cout << "? ³���������� �� ��������� ��������.\n";
}

// ---------------- Գ�������� ----------------
void CarManager::filterByBrand(const string& b) const {
    cout << "\nԳ���� �� ������: " << b << "\n";
    bool found = false;
    for (const auto& car : cars) {
        if (car->isBrand(b)) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? ���� ���� � ����� ������.\n";
}

void CarManager::filterByColor(const string& color) const {
    cout << "\nԳ���� �� ��������: " << color << "\n";
    bool found = false;
    for (const auto& car : cars) {
        if (car->getColor() == color) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? ���� ���� � ����� ��������.\n";
}

void CarManager::filterByYear(int year) const {
    cout << "\nԳ���� �� �����: " << year << "\n";
    bool found = false;
    for (const auto& car : cars) {
        if (car->getYear() == year) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? ���� ���� ����� ����.\n";
}

void CarManager::showCarAge() const {
    int index;
    showAllCars();
    cout << "\n������ ������ ���� ��� �������� ���: "; cin >> index;

    if (index >= 0 && index < cars.size()) {
        cout << "³� ����: " << cars[index]->getAge() << " ����\n";
    }
    else {
        cout << "? ������� ������.\n";
    }
}

// ---------------- ��� ������ ----------------
void CarManager::findByBrand() const {
    string b;
    cout << "\n������ ����� ��� ������: "; cin >> b;
    filterByBrand(b);
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


void CarManager::findEconomicalCars() const {
    double limit;
    cout << "������ ��� ������ �������� (���/100��): "; cin >> limit;
    bool found = false;
    for (const auto& car : cars) {
        if (car->isEconomical(limit)) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? ���� ���� ���������� �� " << limit << " �/100��.\n";
}

void CarManager::findFamilyCars() const {
    cout << "\nѳ���� ���� (>=4 ������):\n";
    bool found = false;
    for (const auto& car : cars) {
        if (car->isFamilyCar()) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? ѳ������ ���� ����.\n";
}

void CarManager::filterByModel(const string& m) const {
    cout << "\nԳ���� �� �������: " << m << "\n";
    bool found = false;
    for (const auto& car : cars) {
        if (car->getModel() == m) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? ���� ���� � ����� �������.\n";
}

void CarManager::applyDiscountToCar() {
    int index;
    double percent;
    showAllCars();
    cout << "\n������ ������ ���� ��� ������: "; cin >> index;
    cout << "������ ������� ������: "; cin >> percent;

    if (index >= 0 && index < cars.size()) {
        cars[index]->applyDiscount(percent);
        cout << "? ������ �����������!\n";
        cars[index]->print();
    }
    else {
        cout << "? ������� ������.\n";
    }
}

void CarManager::calcTripCost() const {
    int index;
    double distance, fuelPrice;
    showAllCars();
    cout << "\n������ ������ ����: "; cin >> index;
    cout << "������ ������� ������ (��): "; cin >> distance;
    cout << "������ ���� �� ��� �������� (���): "; cin >> fuelPrice;

    if (index >= 0 && index < cars.size()) {
        double cost = cars[index]->costPer100km(fuelPrice) * (distance / 100.0);
        cout << "������� ������: " << cost << " ���\n";
    }
    else {
        cout << "? ������� ������.\n";
    }
}

void CarManager::showHelp() const {
    cout << "\n--- ������ (��� ������������) ---\n";
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
    cout << "22. �������� (��� ������)\n";
    cout << "23. ����� � ��������\n";

}
void CarManager::showHelpnotadm() const {
    cout << "\n--- ������ (��� �����������) ---\n";
    cout << "1. ����������� �� ����\n";
    cout << "2. ������������� ����\n";
    cout << "3. ������� ���� � �����\n";
    cout << "4. ����� ���� �� ���������\n";
    cout << "5. ��������� �� ����� (���������)\n";
    cout << "6. ��������� �� ����� (��������)\n";
    cout << "7. ��������� �� ����� (���������)\n";
    cout << "8. ��������� �� ����� (��������)\n";
    cout << "9. Գ���� �� ��������\n";
    cout << "10. Գ���� �� �����\n";
    cout << "11. �������� (��� ������)\n";
    cout << "12. ����� � ��������\n";
}
