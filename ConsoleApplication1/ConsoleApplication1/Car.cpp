#include "Car.h"
using namespace std;

Car::Car()
    : Vehicle(), model("Unknown"), fuelConsumption(0.0), doorCount(0), config() {
    cout << "[Car] ����������� �� �������������\n";
}

Car::Car(const string& b, const string& c, const string& m,
    double fuel, int doors, int y, double p, const Configuration& cfg)
    : Vehicle(b, c, y, p, m),
    model(m),
    fuelConsumption(fuel),
    doorCount(doors),
    config(cfg) {
    cout << "[Car] ����������� � �����������: " << brand << " " << model << endl;
}

Car::Car(const Car& other)
    : Vehicle(other),
    model(other.model),
    fuelConsumption(other.fuelConsumption),
    doorCount(other.doorCount),
    config(other.config) {
    cout << "[Car] ����������� �����������: " << brand << " " << model << endl;
}

Car::Car(Car&& other) noexcept
    : Vehicle(move(other)),
    model(std::move(other.model)),
    fuelConsumption(other.fuelConsumption),
    doorCount(other.doorCount),
    config(std::move(other.config)) {
    cout << "[Car] �������������� �����������: " << brand << " " << model << endl;
}

Car::~Car() {
    cout << "[Car] �������: " << brand << " " << model << endl;
}

void Car::print() const {
    cout << "�����: " << brand
        << ", ������: " << model
        << ", ����: " << color
        << ", ������� �������: " << fuelConsumption << " �/100��"
        << ", ʳ������ ������: " << doorCount
        << ", г�: " << year
        << ", ֳ��: " << price << " ���" << endl;
    config.print();
}

Car Car::fromCSV(const string& line) {
    istringstream iss(line);
    string brand, color, model;
    double fuelConsumption, price;
    int doorCount, year;

    getline(iss, brand, ',');
    getline(iss, color, ',');
    getline(iss, model, ',');
    iss >> fuelConsumption; iss.ignore();
    iss >> doorCount; iss.ignore();
    iss >> year; iss.ignore();
    iss >> price;

    if (iss.peek() == ',') iss.get(); // ���������� ����
    string configData;
    getline(iss, configData);

    Configuration cfg;
    if (!configData.empty()) {
        cfg = Configuration::fromCSV(configData);
    }

    return Car(brand, color, model, fuelConsumption, doorCount, year, price, cfg);
}

string Car::toCSV() const {
    ostringstream oss;
    oss << brand << "," << color << "," << model << ","
        << fuelConsumption << "," << doorCount << ","
        << year << "," << price << ","
        << config.toCSV();
    return oss.str();
}

// Getters
double Car::getFuelConsumption() const { return fuelConsumption; }
int Car::getDoorCount() const { return doorCount; }

// Setters
void Car::setFuelConsumption(double f) { fuelConsumption = f; }
void Car::setDoorCount(int d) { doorCount = d; }

bool Car::isEconomical(double limit) const { return fuelConsumption < limit; }
bool Car::isFamilyCar() const { return doorCount >= 4; }
bool Car::compareByFuel(const Car& other) const { return fuelConsumption < other.fuelConsumption; }
bool Car::isNewerThan(int y) const { return year > y; }
double Car::costPer100km(double fuelPrice) const { return (fuelConsumption / 100.0) * fuelPrice * 100; }

int Car::getAge() const {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    int currentYear = 1900 + ltm.tm_year;
    return currentYear - year;
}

string Car::getModel() const { return model; }
void Car::setModel(const string& m) { model = m; }
