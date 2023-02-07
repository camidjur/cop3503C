#include "Color.h"
#include <string>
string Color::toHex(int num) {
	int quotient;
	int temp;
	string hex = "";
	temp = num / 16;
	if (temp <= 9) {
		hex += to_string(temp);
	}
	else {
		if (temp == 10) {
			hex += 'A';
		}
		if (temp == 11) {
			hex += 'B';
		}
		if (temp == 12) {
			hex += 'C';
		}
		if (temp == 13) {
			hex += 'D';
		}
		if (temp == 14) {
			hex += 'E';
		}
		if (temp == 15) {
			hex += 'F';
		}
	}

	quotient = num % 16;
	if (quotient <= 9) {
		hex += to_string(quotient);
	}
	else {
		if (quotient == 10) {
			hex += 'A';
		}
		if (quotient == 11) {
			hex += 'B';
		}
		if (quotient == 12) {
			hex += 'C';
		}
		if (quotient == 13) {
			hex += 'D';
		}
		if (quotient == 14) {
			hex += 'E';
		}
		if (quotient == 15) {
			hex += 'F';
		}
	}
	return hex;

}
Color::Color() {
	name = "";
	red = 0;
	green = 0;
	blue = 0;
	hex = "";
}
Color::Color(string name, unsigned char red, unsigned char green, unsigned char blue) {
	this->name = name;
	this->red = red;
	this->green = green;
	this->blue = blue;

	// transform hex
	hex = "0x";
	hex += toHex(red);
	hex += toHex(green);
	hex += toHex(blue);
}
string Color::GetName() const {
	return name;
}
string Color::GetHexValue() const {
	return hex;
}
unsigned char Color::GetR() const {
	return red;
}
unsigned char Color::GetG() const {
	return green;
}
unsigned char Color::GetB() const {
	return blue;
}