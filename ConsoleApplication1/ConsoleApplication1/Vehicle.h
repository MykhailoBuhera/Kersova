#pragma once
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
	Vehicle& operator=(const Vehicle& other);
    // ������������
    Vehicle();
    Vehicle(const string& b, const string& c, int y, double p, const string& m);
    Vehicle(const Vehicle& other);
    Vehicle(Vehicle&& other) noexcept;

    // ³��������� ����������
    virtual ~Vehicle();

    // Getters
    string getBrand() const;
    string getColor() const;
    int getYear() const;
    double getPrice() const;
    string getModel() const;

    // Setters
    void setBrand(const string& b);
    void setColor(const string& c);
    void setYear(int y);
    void setPrice(double p);

    // ������ ��������� ������
    bool isOlderThan(int y) const;          // �� ������� �� ��
    bool isCheaperThan(double p) const;     // �� �������� �� ����
    int age(int currentYear) const;         // ³� ����
    void applyDiscount(double percent);     // ������
    bool isBrand(const string& b) const;    // �� ������� �����

    // ³������� ������ ��� ��������� � ��������

    virtual void print() const = 0;
    virtual string toCSV() const = 0;

protected:
    string brand;
    string model;
    string color;
    int year;
    double price;

};
