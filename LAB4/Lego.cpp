#include <string>
#include <iostream>
#include <vector>
#include "Lego.h"
using namespace std;

Lego::Lego() {
	setNum = "";
	theme = "";
	name = "";
	minifigNum = 0;
	piecesNums = 0;
	price = 0.0;
}
Lego::Lego(string setNum, string theme, string name, unsigned int minifigNum,
	unsigned int partNums, double price) {
	this->setNum = setNum;
	this->theme = theme;
	this->name = name;
	this->minifigNum = minifigNum;
	this->piecesNums = partNums;
	this->price = price;
}
double Lego::GetPrice() {
	return price;
}
string Lego::GetSetNum() {
	return setNum;
}
string Lego::GetName() {
	return name;
}
string Lego::GetTheme() {
	return theme;
}
unsigned int Lego::GetMinifigs() {
	return minifigNum;
}
unsigned int Lego::GetPieces() {
	return piecesNums;
}