#pragma once
#include "TextureManager.h"
#include<vector>
using std::vector;

class Tiles
{
private:
	sf::Sprite hidden;
	sf::Sprite revealed;
	sf::Sprite bomb;
	sf::Sprite flag;
	sf::Sprite number;
	bool isItRevealed;
	bool isItFlagged;
	bool isItMine;

public:
	Tiles(sf::Sprite hidden, sf::Sprite revealed, sf::Sprite bomb,
		sf::Sprite flag, bool isItRevealed, bool isItFlagged, bool isItMine);
	sf::Sprite& getHidden();
	sf::Sprite& getRevealed();
	sf::Sprite& getBomb();
	sf::Sprite& getFlag();
	sf::Sprite& getNum();
	void setNum(int num);
	void setRevealed(bool state);
	void setFlagged(bool state);
	void setMined(bool state);
	bool getRevealedState();
	bool getFlaggedState();
	bool getMineState();
	sf::Sprite makeItRect(sf::Sprite& original, sf::Vector2i& position, sf::Vector2i& size);
};

