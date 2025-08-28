#include "Configuration.h"
#include "Car.h"
#include <sstream>

// Конструктор за замовчуванням
Configuration::Configuration()
    : Vehicle("Unknown", "Unknown", 0, 0.0, ""), packageName("Basic"),
      hasAirConditioner(false), hasMultimedia(false), hasSafetySystem(false), price(0.0) {
}

// Конструктор з параметрами
Configuration::Configuration(const std::string& brand, const std::string& model,
    const std::string& packageName, bool ac, bool multimedia, bool safety, double price)
    : Vehicle(brand, model, 0, 0.0,""), packageName(packageName),
    hasAirConditioner(ac), hasMultimedia(multimedia), hasSafetySystem(safety), price(price) {
}

// Конструктор копіювання
Configuration::Configuration(const Configuration& other)
    : Vehicle(other), packageName(other.packageName),
    hasAirConditioner(other.hasAirConditioner), hasMultimedia(other.hasMultimedia),
    hasSafetySystem(other.hasSafetySystem), price(other.price) {
}

// Конструктор переміщення
Configuration::Configuration(Configuration&& other) noexcept
    : Vehicle(std::move(other)), packageName(std::move(other.packageName)),
    hasAirConditioner(other.hasAirConditioner), hasMultimedia(other.hasMultimedia),
    hasSafetySystem(other.hasSafetySystem), price(other.price) {
}

// Деструктор
Configuration::~Configuration() {
    std::cout << "Configuration destroyed: \n " << packageName;
}

// Get/Set
std::string Configuration::getPackageName() const { return packageName; }
void Configuration::setPackageName(const std::string& name) { packageName = name; }

double Configuration::getPrice() const { return price; }
void Configuration::setPrice(double p) { price = p; }

// Методи предметної області
bool Configuration::isLuxury() const {
    return hasAirConditioner && hasMultimedia && hasSafetySystem;
}

void Configuration::toggleAirConditioner() { hasAirConditioner = !hasAirConditioner; }
void Configuration::toggleMultimedia() { hasMultimedia = !hasMultimedia; }
void Configuration::toggleSafety() { hasSafetySystem = !hasSafetySystem; }

// Вивід інформації
void Configuration::print() const {
    std::cout << "Configuration: " << packageName
        << " | Car: " << getBrand() << " " << getModel()
        << " | AC: " << (hasAirConditioner ? "Yes" : "No")
        << " | Multimedia: " << (hasMultimedia ? "Yes" : "No")
        << " | Safety: " << (hasSafetySystem ? "Yes" : "No")
        << " | Price: " << price << std::endl;
}

// CSV збереження
std::string Configuration::toCSV() const {
    return getBrand() + "," + getModel() + "," + packageName + "," +
        (hasAirConditioner ? "1" : "0") + "," +
        (hasMultimedia ? "1" : "0") + "," +
        (hasSafetySystem ? "1" : "0") + "," +
        std::to_string(price);
}

// CSV читання
Configuration Configuration::fromCSV(const std::string& line) {
    std::stringstream ss(line);
    std::string brand, model, pkg, acStr, mmStr, safetyStr, priceStr;

    std::getline(ss, brand, ',');
    std::getline(ss, model, ',');
    std::getline(ss, pkg, ',');
    std::getline(ss, acStr, ',');
    std::getline(ss, mmStr, ',');
    std::getline(ss, safetyStr, ',');
    std::getline(ss, priceStr, ',');

    return Configuration(brand, model, pkg, acStr == "1", mmStr == "1", safetyStr == "1", std::stod(priceStr));
}
