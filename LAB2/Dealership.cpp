#include "Dealership.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

Dealership::Dealership(string name, unsigned int capacity) {
	dealershipName = name;
	dealershipCapacity = capacity;
}
void Dealership::AddShowroom(Showroom s) {
	if (showroomsInDealership.size() == dealershipCapacity) {
		cout << "Dealership is full, can't add another showroom!" << endl;
	}
	else {
		showroomsInDealership.push_back(s);
	}
}
float Dealership::GetAveragePrice() {
	float showroomsTotalValue = 0.0;
	int totalNumOfCars = 0;
	float averagePrice = 0.00;
	
	for (unsigned int i = 0; i < showroomsInDealership.size(); i++) {
		showroomsTotalValue += showroomsInDealership.at(i).GetInventoryValue();
		totalNumOfCars += showroomsInDealership.at(i).GetVehicleList().size();
	}
	averagePrice = showroomsTotalValue / totalNumOfCars;
	// printf

	return averagePrice;
}
void Dealership::ShowInventory() {
	if (showroomsInDealership.size() == 0) {
		cout << dealershipName + " is empty!" << endl;
		cout << "Average car price: $0.00";
	}
	else {
		for (unsigned int i = 0; i < showroomsInDealership.size(); i++) {
			showroomsInDealership.at(i).ShowInventory();
			cout << endl;
		}
		cout << "Average car price: $";
		cout << this->GetAveragePrice();
	}
	
	
}