#pragma once
#include <string>
using namespace std;


class Lego {
private:
	string setNum;
	string theme;
	string name;
	unsigned int minifigNum;
	unsigned int piecesNums;
	double price;
public:
	Lego();
	Lego(string setNum, string theme, string name, unsigned int minifigNum,
		unsigned int piecesNums, double price);
	string GetSetNum();
	double GetPrice();
	string GetName();
	string GetTheme();
	unsigned int GetMinifigs();
	unsigned int GetPieces();
};
