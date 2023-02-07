#pragma once
#include <string>
#include <vector>
#include "Vehicle.h"
#include "Showroom.h"
using namespace std;


class Dealership {
private:
	string dealershipName;
	unsigned int dealershipCapacity;
	vector <Showroom> showroomsInDealership;
public:
	Dealership(string name = "Generic Dealership", unsigned int capacity = 0);
	void AddShowroom(Showroom s);
	float GetAveragePrice();
	void ShowInventory();

};
