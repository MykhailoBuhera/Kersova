#include "Vehicle.h"
using namespace std;
Vehicle::Vehicle(string b, string c, int y, double p)
    : brand(b), color(c), year(y), price(p) {
}

int Vehicle::getYear() const { return year; }
double Vehicle::getPrice() const { return price; }
