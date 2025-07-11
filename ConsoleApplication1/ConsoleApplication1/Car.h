#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <sstream>

class Car : public Vehicle {
private:
    double fuelConsumption;
    int doorCount;

public:
    Car(std::string b, std::string c, double fuel, int doors, int y, double p);

    double getFuelConsumption() const;
    void print() const override;
    std::string toCSV() const override;

    static Car fromCSV(const std::string& line);
};

#endif
