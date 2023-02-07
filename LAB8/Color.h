#pragma once
#include <string>
using namespace std;

class Color
{
private:
	string name;
	string hex;
	unsigned char red;
	unsigned char blue;
	unsigned char green;
public:
	Color();
	Color(string name, unsigned char red, unsigned char green, unsigned char blue);
	string GetName() const;
	string GetHexValue() const;
	unsigned char GetR() const;
	unsigned char GetG() const;
	unsigned char GetB() const;
	string toHex(int num);
};

