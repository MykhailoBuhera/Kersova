#include "Car.h"
#include <iostream>
using namespace std;

Car::Car(string b, string c, double fuel, int doors, int y, double p)
    : Vehicle(b, c, y, p), fuelConsumption(fuel), doorCount(doors) {
}

double Car::getFuelConsumption() const {
    return fuelConsumption;
}

void Car::print() const {
   cout << "Марка: " << brand
        << ", Колір: " << color
        << ", Витрати бензину: " << fuelConsumption << " л/100км"
        << ", Кількість дверей: " << doorCount
        << ", Рік: " << year
        << ", Ціна: " << price << " грн" << endl;
}

string Car::toCSV() const {
    ostringstream oss;
    oss << brand << ',' << color << ',' << fuelConsumption << ','
        << doorCount << ',' << year << ',' << price;
    return oss.str();
}

Car Car::fromCSV(const string& line) {
    istringstream iss(line);
    string b, c;
    double f, p;
    int d, y;
    getline(iss, b, ',');
    getline(iss, c, ',');
    iss >> f; iss.ignore();
    iss >> d; iss.ignore();
    iss >> y; iss.ignore();
    iss >> p;
    return Car(b, c, f, d, y, p);
}
