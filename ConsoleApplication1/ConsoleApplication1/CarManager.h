#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Car.h"
#include "Configuration.h"

using namespace std;

class CarManager {
private:
    vector<shared_ptr<Car>> cars;

    void printCarIndexList() const;

public:
    // --- CRUD ---
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename);
    void addCar();
    void showAllCars() const;
    void editCar();
    void removeCar();

    // --- �������� ---
    void findMostEconomicalCar() const;
    void averagePriceInPeriod() const;

    // --- ���������� ---
    void sortByPrice(bool ascending = true);
    void sortByYear(bool ascending = true);
    void sortByFuelConsumption(bool ascending = true);

    // --- Գ�������� ---
    void filterByBrand(const string& b) const;
    void filterByColor(const string& c) const;
    void filterByYear(int y) const;
	void filterByModel(const string& m) const;

    // --- ��� ������ (� ��������� ������) ---
    void findByBrand() const;
    void findEconomicalCars() const;
    void findFamilyCars() const;
    void applyDiscountToCar();
    void showCarAge() const;
    void calcTripCost() const;
    void searchCars() const;
    // --- �������� ����� ---
    void showHelp() const;
    void showHelpnotadm() const;
};
