#pragma once
#include <string>
#include <vector>
using namespace std;
class Weapons
{
private:
	string weaponName;
	int powerRating;
	float powerCons;

public:
	Weapons();
	Weapons(string name, int rating, float consumption);
	void PrintWeapons();
	int GetPower();
};

class Ship
{
private:
	string name;
	string className;
	short shipLength;
	int capacity;
	float maxSpeed;
	vector<Weapons> weapons;

public:
	Ship();
	Ship(string shipName, string shipClass, short shipL,
		int shipCap, float speed, vector<Weapons>& shipWeapons);
	void PrintAll();
	int TotalFirePower();
	int StrongestWeapon();
	int WeakestShip();
	bool UnarmedShip();
};

