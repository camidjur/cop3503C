#include "Vehicle.h"
#include <string>
#include <iostream>
using namespace std;

Vehicle::Vehicle() {
	carMake = "COP3503";
	carModel = "Rust Bucket";
	carYear = 1900;
	carPrice = 0;
	carMileage = 0;
}
Vehicle::Vehicle(string make, string model, int year, float price, int mileage) {
	carMake = make;
	carModel = model;
	carYear = year;
	carPrice = price;
	carMileage = mileage;
}
void Vehicle::Display() {
	cout << to_string(carYear) + " " + carMake + " " + carModel + " $";
	cout << carPrice;
	cout << " " + to_string(carMileage) << endl;
 }
string Vehicle::GetYearMakeModel() {
	string result = to_string(carYear) + " " + carMake + " " + carModel;
	return result;
}
float Vehicle::GetPrice() {
	return carPrice;
}