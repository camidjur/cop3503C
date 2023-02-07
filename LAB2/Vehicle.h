#pragma once
#include <string>
using namespace std;


class Vehicle {
private:
	string carMake;
	string carModel;
	unsigned int carYear;
	float carPrice;
	unsigned int carMileage;

public:
	Vehicle();
	Vehicle(string make, string model, int year, float price, int mileage);
	void Display();
	string GetYearMakeModel();
	float GetPrice();

};

