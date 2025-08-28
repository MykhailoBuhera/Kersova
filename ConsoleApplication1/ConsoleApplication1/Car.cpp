#include "Car.h"
using namespace std;
Car::Car()
    : Vehicle(), model("Unknown"), fuelConsumption(0.0), doorCount(0) {
    cout << "[Car] Конструктор за замовчуванням\n";
}

// Додано новий конструктор з параметром моделі
Car::Car(const string& b, const string& c, const string& m, double fuel, int doors, int y, double p, const Configuration& config)
    : Vehicle(b, c, y, p, m), model(m), fuelConsumption(fuel), doorCount(doors) {
    cout << "[Car] Конструктор з параметрами: " << brand << " " << model << endl;
}

Car::Car(const Car& other)
    : Vehicle(other), model(other.model),
    fuelConsumption(other.fuelConsumption), doorCount(other.doorCount) {
    cout << "[Car] Копіювальний конструктор: " << brand << " " << model << endl;
}

Car::Car(Car&& other) noexcept
    : Vehicle(move(other)), model(std::move(other.model)),
    fuelConsumption(other.fuelConsumption), doorCount(other.doorCount) {
    cout << "[Car] Переміщувальний конструктор: " << brand << " " << model << endl;
}

// === Деструктор ===
Car::~Car() {
    cout << "[Car] Знищено: " << brand << " " << model << endl;
}

// === print() — додали вивід моделі ===
void Car::print() const {
    cout << "Марка: " << brand
        << ", Модель: " << model
        << ", Колір: " << color
        << ", Витрати бензину: " << fuelConsumption << " л/100км"
        << ", Кількість дверей: " << doorCount
        << ", Рік: " << year
        << ", Ціна: " << price << " грн" << endl;
        config.print();
}

// === CSV — вставили model між color і fuel ===
string Car::toCSV() const {
    ostringstream oss;
    oss << brand << "," << color << "," << getModel() << ","
        << fuelConsumption << ","
        << doorCount << ","
        << year << ","
        << price;
    return oss.str();
}

Car Car::fromCSV(const string& line) {
    istringstream iss(line);
    string b, c, m;
    double f, p;
    int d, y;

    getline(iss, b, ',');     // brand
    getline(iss, c, ',');     // color
    getline(iss, m, ',');     // model  <— НОВЕ
    iss >> f; iss.ignore();   // fuelConsumption
    iss >> d; iss.ignore();   // doorCount
    iss >> y; iss.ignore();   // year
    iss >> p;                 // price
	Configuration config;
    return Car(b, c, m, f, d, y, p, config);
}

// Getters
double Car::getFuelConsumption() const { return fuelConsumption; }
int Car::getDoorCount() const { return doorCount; }

// Setters
void Car::setFuelConsumption(double f) { fuelConsumption = f; }
void Car::setDoorCount(int d) { doorCount = d; }

// Методи предметної області
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
