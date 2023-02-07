#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Ship.h"
using namespace std;

void LoadingFiles(string fileName, vector<Ship>& ships){
	// load file 
	ifstream inFile(fileName, ios_base::binary);
	if (inFile.is_open()) {

		// get count 
		unsigned int count;
		inFile.read((char*)&count, sizeof(count));

		unsigned int length;
		char* buffer;
		string name;
		string className;
		short shipLength;
		int capacity;
		float maxSpeed;

		vector<Weapons> weapons;
		unsigned int numOfWeapons;
		string weaponName;
		int powerRating;
		float powerCons;
		// loop count number of times 
		for (unsigned int i = 0; i < count; i++) {

			//getting the name
			inFile.read((char*)&length, sizeof(length));
			buffer = new char[length];
			inFile.read(buffer, length);
			name = buffer;
			delete[] buffer;

			//getting class name 
			inFile.read((char*)&length, sizeof(length));
			buffer = new char[length];
			inFile.read(buffer, length);
			className = buffer;
			delete[] buffer;

			//getting ship's length
			inFile.read((char*)&shipLength, sizeof(shipLength));

			//getting ship's capacity
			inFile.read((char*)&capacity, sizeof(capacity));

			//getting wrap speed
			inFile.read((char*)&maxSpeed, sizeof(maxSpeed));

			//getting weapons
			inFile.read((char*)&numOfWeapons, sizeof(numOfWeapons));
			for (unsigned int j = 0; j < numOfWeapons; j++) {

				//getting weapon name 
				inFile.read((char*)&length, sizeof(length));
				buffer = new char[length];
				inFile.read(buffer, length);
				weaponName = buffer;
				delete[] buffer;

				//getting power rating 
				inFile.read((char*)&powerRating, sizeof(powerRating));

				//getting power consumption
				inFile.read((char*)&powerCons, sizeof(powerCons));

				// creating vector with weapon info 
				Weapons w(weaponName, powerRating, powerCons);
				weapons.push_back(w);
			}

			// adds ship w all info to vector 
			Ship s(name, className, shipLength, capacity, maxSpeed, weapons);
			ships.push_back(s);

			weapons.clear();
		}
	}

}

int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

	/* Load files here */
	vector<Ship> Ships;
	if (option == 1) {
		LoadingFiles("friendlyships.shp", Ships);
	}
	else if (option == 2) {
		LoadingFiles("enemyships.shp", Ships);
	}
	else if (option == 3) {
		LoadingFiles("friendlyships.shp", Ships);
		LoadingFiles("enemyships.shp", Ships);
	}

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;

	cin >> option;

	/* Work your magic here */
	if (option == 1) {
		for (unsigned int i = 0; i < Ships.size(); i++) {
			Ships[i].PrintAll();
			cout << endl;
		}
	}
	else if (option == 2) {
		unsigned int temp = 0;
		int strongest = 0;
		for (unsigned int i = 0; i < Ships.size(); i++) {
			if (Ships[i].StrongestWeapon() > strongest) {
				strongest = Ships[i].StrongestWeapon();
				temp = i;
			}
		}
		cout << "Starship with the strongest weapon:" << endl;
		Ships[temp].PrintAll();
	}
	else if (option == 3) {
		int strongest = 0;
		unsigned int temp = 0;
		for (unsigned int i = 0; i < Ships.size(); i++) {
			if (Ships[i].TotalFirePower() > strongest) {
				strongest = Ships[i].TotalFirePower();
				temp = i;
			}
		}
		cout << "Strongest starship overall: " << endl;
		Ships[temp].PrintAll();
	}
	else if (option == 4) {
		unsigned int temp = 0;
		int weakest = Ships[0].WeakestShip();
		for (unsigned int i = 0; i < Ships.size(); i++) {
			if (Ships[i].WeakestShip() == 0) {
				continue;
			}
			if (Ships[i].WeakestShip() < weakest) {
				weakest = Ships[i].WeakestShip();
				temp = i;
			}
		}
		cout << "Weakest ship: " << endl;
		Ships[temp].PrintAll();
	}
	else if (option == 5) {
		vector<Ship> unarmedShips;
		for (unsigned int i = 0; i < Ships.size(); i++) {
			if (Ships[i].UnarmedShip()) {
				unarmedShips.push_back(Ships[i]);
			}
		}
		cout << "Unarmed Ships: " << endl;
		for (unsigned int j = 0; j < unarmedShips.size(); j++) {
			unarmedShips[j].PrintAll();
		}
	}

	return 0;
}