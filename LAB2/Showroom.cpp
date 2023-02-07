#include <string>
#include <iostream>
#include "Showroom.h"
using namespace std;

Showroom::Showroom(string name, unsigned int capacity) {
	showroomName = name;
	maximumCapacity = capacity;

}
vector <Vehicle> Showroom ::GetVehicleList() {
	return vehiclesInShowroom;
}
void Showroom::AddVehicle(Vehicle v) {
	if (vehiclesInShowroom.size() == maximumCapacity) {
		cout << "Showroom is full! Cannot add " + v.GetYearMakeModel() << endl;
	}
	else {
		vehiclesInShowroom.push_back(v);
	}
}
void Showroom::ShowInventory() {
	if (vehiclesInShowroom.size() == 0) {
		cout << showroomName + " is empty!" << endl;
	}
	else {
		cout << "Vehicles in " + showroomName << endl;
		for (unsigned int i = 0; i < vehiclesInShowroom.size(); i++) {
			vehiclesInShowroom.at(i).Display();
		}
	}
	
}
float Showroom :: GetInventoryValue() {
	float resultPrice = 0;
	for (unsigned int i = 0; i < vehiclesInShowroom.size(); i++) {
		resultPrice += vehiclesInShowroom.at(i).GetPrice();
	}
	return resultPrice;
}