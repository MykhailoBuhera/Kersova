#ifndef VEHICLE_H
#define VEHICLE_H

#include "IPrintable.h"
#include <string>

class Vehicle : public IPrintable {
protected:
    std::string brand;
    std::string color;
    int year;
    double price;


public:
    Vehicle(std::string b, std::string c, int y, double p);
    virtual int getYear() const;
    virtual double getPrice() const;
    virtual ~Vehicle() {}
};

#endif
