#ifndef CARMANAGER_H
#define CARMANAGER_H

#include "Car.h"
#include <vector>
#include <memory>
#include <string>
using namespace std;

class CarManager {
private:
    vector<shared_ptr<Car>> cars;

public:
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename);
    void addCar();
    void showAllCars() const;
    void findMostEconomicalCar() const;
    void averagePriceInPeriod() const;
    void editCar();
    void deleteCar();
    void searchCars() const;
    void sortByPrice(bool ascending = true);
    void sortByYear(bool ascending = true);

};

#endif
