#pragma once
#include "Vehicle.h"
#include <sstream>
#include "Configuration.h"

class Car : public Vehicle {
private:
    Configuration config;
    double fuelConsumption;
    int doorCount;
    std::string model;

public:
    // ������������
    Car();
    Car(const std::string& b, const std::string& c, const std::string& m, double fuel, int doors, int y, double p, const Configuration& config);
    Car(const Car& other);
    Car(Car&& other) noexcept;

    // ����������
    ~Car();

    // Getters
    double getFuelConsumption() const;
    int getDoorCount() const;

    // Setters
    void setFuelConsumption(double f);
    void setDoorCount(int d);

    // ������ ��������� ������
    bool isEconomical(double limit) const;       // �����������
    bool isFamilyCar() const;                    // ѳ����� ���� (>=4 ������)
    bool compareByFuel(const Car& other) const;  // ��������� ������ ��������
    bool isNewerThan(int y) const;               // �� ������ �� ��
    double costPer100km(double fuelPrice) const; // ������� ������ �� 100 ��
    int getAge() const;
    // ��������� ����������� ������
    void print() const override;
    string toCSV() const override;
    std::string getModel() const;
    void setModel(const std::string& m);

    static Car fromCSV(const string& line);
};
