#pragma once
#include "Vehicle.h"
#include "IPrintable.h"
#include <string>
#include <iostream>

class Configuration : public Vehicle, public IPrintable {
public:
    Configuration& operator=(const Configuration& other);

    // Конструктор за замовчуванням
    Configuration();

    // Конструктор з параметрами
    Configuration(const std::string& brand, const std::string& model,
        const std::string& packageName, bool ac, bool multimedia, bool safety, double price);

    // Конструктор копіювання
    Configuration(const Configuration& other);

    // Конструктор переміщення
    Configuration(Configuration&& other) noexcept;

    // Деструктор
    ~Configuration();

    // Get/Set
    std::string getPackageName() const;
    void setPackageName(const std::string& name);

    double getPrice() const;
    void setPrice(double p);

    // Методи предметної області
    bool isLuxury() const; // чи "преміум"
    void toggleAirConditioner();
    void toggleMultimedia();
    void toggleSafety();

    // Перевизначення
    void print() const override;
    std::string toCSV() const override;
    static Configuration fromCSV(const std::string& line);
private:
    std::string packageName;   // Назва комплектації (Basic, Comfort, Premium)
    bool hasAirConditioner;
    bool hasMultimedia;
    bool hasSafetySystem;
    double price;

};
