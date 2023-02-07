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

