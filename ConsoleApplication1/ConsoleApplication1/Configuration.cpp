#include "Configuration.h"
#include <sstream>

// Конструктор за замовчуванням
Configuration::Configuration()
    : Vehicle("Unknown", "", 0, 0.0, "Unknown"),
    packageName("Basic"),
    hasAirConditioner(false),
    hasMultimedia(false),
    hasSafetySystem(false),
    price(0.0) {
}

// Конструктор з параметрами
Configuration::Configuration(const std::string& brand, const std::string& model,
    const std::string& packageName, bool ac, bool multimedia, bool safety, double price)
    : Vehicle(brand, "", 0, 0.0, model),
    packageName(packageName),
    hasAirConditioner(ac),
    hasMultimedia(multimedia),
    hasSafetySystem(safety),
    price(price) {
}

// Конструктор копіювання
Configuration::Configuration(const Configuration& other)
    : Vehicle(other),
    packageName(other.packageName),
    hasAirConditioner(other.hasAirConditioner),
    hasMultimedia(other.hasMultimedia),
    hasSafetySystem(other.hasSafetySystem),
    price(other.price) {
}

// Конструктор переміщення
Configuration::Configuration(Configuration&& other) noexcept
    : Vehicle(std::move(other)),
    packageName(std::move(other.packageName)),
    hasAirConditioner(other.hasAirConditioner),
    hasMultimedia(other.hasMultimedia),
    hasSafetySystem(other.hasSafetySystem),
    price(other.price) {
}

// Деструктор
Configuration::~Configuration() {
    std::cout << "Configuration destroyed: " << packageName << std::endl;
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
        << " | AC: " << (hasAirConditioner ? "Yes" : "No")
        << " | Multimedia: " << (hasMultimedia ? "Yes" : "No")
        << " | Safety: " << (hasSafetySystem ? "Yes" : "No")
        << " | Price: " << price << std::endl;
}

std::string Configuration::toCSV() const {
    std::ostringstream oss;
    oss << packageName << ","
        << hasAirConditioner << ","
        << hasMultimedia << ","
        << hasSafetySystem << ","
        << price;
    return oss.str();
}

Configuration Configuration::fromCSV(const std::string& line) {
    std::istringstream iss(line);
    std::string packageName;
    bool hasAirConditioner, hasMultimedia, hasSafetySystem;
    double price;

    getline(iss, packageName, ',');
    iss >> hasAirConditioner; iss.ignore();
    iss >> hasMultimedia; iss.ignore();
    iss >> hasSafetySystem; iss.ignore();
    iss >> price;

    return Configuration("Unknown", "Unknown", packageName, hasAirConditioner, hasMultimedia, hasSafetySystem, price);
}

Configuration& Configuration::operator=(const Configuration& other) {
    if (this != &other) {
        Vehicle::operator=(other); // Call base class assignment
        packageName = other.packageName;
        hasAirConditioner = other.hasAirConditioner;
        hasMultimedia = other.hasMultimedia;
        hasSafetySystem = other.hasSafetySystem;
        price = other.price;
    }
    return *this;
}
