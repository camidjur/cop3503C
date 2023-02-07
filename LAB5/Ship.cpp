#include <iostream>
#include <vector>
#include "Ship.h"
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

Ship::Ship(){
	name = "";
	className = "";
	shipLength = 0;
	capacity = 0;
	maxSpeed = 0.0;
}
Ship::Ship(string shipName, string shipClass, short shipL,
	int shipCap, float speed, vector<Weapons>& shipWeapons) {
	name = shipName;
	className = shipClass;
	shipLength = shipL;
	capacity = shipCap;
	maxSpeed = speed;

	for (unsigned int i = 0; i < shipWeapons.size(); i++) {
		weapons.push_back(shipWeapons[i]);
	}
}
void Ship::PrintAll() {
	cout << "Name: " << this->name << endl;
	cout << "Class: " << this->className << endl;
	cout << "Length: " << this->shipLength << endl;
	cout << "Shield capacity: " << this->capacity << endl;
	cout << "Maximum Warp: " << this->maxSpeed << endl;
	cout << "Armaments: " << endl;

	if (this->weapons.size() == 0) {
		cout << "Unarmed" << endl;
	}
	else {
		for (unsigned int i = 0; i < this->weapons.size(); i++) {
			this->weapons[i].PrintWeapons();
		}
		cout << "Total firepower: " << TotalFirePower() << endl;
		
	}
}
int Ship::TotalFirePower() {
	int totalFire = 0;
	for (unsigned int i = 0; i < this->weapons.size(); i++) {
		totalFire += weapons[i].GetPower();
	}
	return totalFire;
}
int Ship::StrongestWeapon() {
	int strongest = 0;
	for (unsigned int i = 0; i < this->weapons.size(); i++) {
		if (this->weapons[i].GetPower() > strongest) {
			strongest = weapons[i].GetPower();
		}
	}
	return strongest;
}
int Ship::WeakestShip() {
	if (this->weapons.size() == 0) {
		return 0;
	}
	int weakest = this->weapons[0].GetPower();
	for (unsigned int i = 0; i < this->weapons.size(); i++) {
		if (this->weapons[i].GetPower() < weakest) {
			weakest = weapons[i].GetPower();
		}
	}
	return weakest;
}
bool Ship::UnarmedShip(){
	if (this->weapons.size() == 0) {
		return true;
	}
	return false;
}