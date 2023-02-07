#include "Tiles.h"
#include <string>
using namespace std;

Tiles::Tiles(sf::Sprite hidden, sf::Sprite revealed,
	sf::Sprite bomb, sf::Sprite flag, bool isItRevealed = false,
	bool isItFlagged = false, bool isItMine = false) {

	this->hidden = hidden;
	this->revealed = revealed;
	this->bomb = bomb;
	this->flag = flag;
	this->isItRevealed = isItRevealed;
	this->isItFlagged  = isItFlagged;
	this->isItMine = isItMine;

}
sf::Sprite& Tiles::getHidden() {
	return hidden;
}
sf::Sprite& Tiles::getRevealed() {
	return revealed;
}

sf::Sprite& Tiles::getBomb() {
	return bomb;
}
sf::Sprite& Tiles::getFlag() {
	return flag;
}
sf::Sprite& Tiles::getNum() {
	return number;
}

void Tiles::setNum(int num) {
	string name = "number_";
	name += to_string(num);
	number.setTexture(TextureManager::GetTexture(name));
}

void Tiles::setRevealed(bool state) {
	if (!getFlaggedState()) {
		isItRevealed = state;
	}
	
}
void Tiles::setFlagged(bool state) {
	isItFlagged = state;
}
void Tiles::setMined(bool state) {
	isItMine = state;
}
bool Tiles::getRevealedState() {
	return isItRevealed;
}
bool Tiles::getFlaggedState() {
	return isItFlagged;
}
bool Tiles::getMineState() {
	return isItMine;
}
sf::Sprite Tiles::makeItRect(sf::Sprite& original, sf::Vector2i& position, sf::Vector2i& size) {
	sf::IntRect r(position, size);
	original.setTextureRect(r);
	return original;
}

