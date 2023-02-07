#include <iostream>
#include <vector>
#include "Weapons.h"
using namespace std;

Weapons::Weapons() {
	weaponName = "";
	powerRating = 0;
	powerCons = 0;
}
Weapons::Weapons(string name, int rating, float consumption) {
	weaponName = name;
	powerRating = rating;
	powerCons = consumption;
}
void Weapons::PrintWeapons() {
	cout << weaponName << ", " << powerRating << ", " << powerCons << endl;
}
int Weapons::GetPower() {
	return this->powerRating;
}

