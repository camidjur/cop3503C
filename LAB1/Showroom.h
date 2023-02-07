#pragma once
#include <string>
#include <vector>
#include "Vehicle.h"
using namespace std;

class Showroom {
private:
	string showroomName;
	vector <Vehicle> vehiclesInShowroom;
	unsigned int maximumCapacity;

public:
	Showroom(string name = "Unnamed Showroom", unsigned int capacity = 0);
	vector <Vehicle> GetVehicleList();
	float GetInventoryValue();


};
