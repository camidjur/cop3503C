#pragma once
#include <vector>
#include "Tiles.h"
using namespace std;

class Board
{
private:
	int width;
	int height;
	int numOfMines;
	int numOfTiles;
	


public:
	Board();
	Board(int width, int height, int mines);
	int GetWidth();
	int GetHeight();
	int GetMines();
	int MinesCloseBy(vector<vector<Tiles>>& t, int x, int y);
	void RecursiveReveal(vector<vector<Tiles>>& t, int x, int y);
	void TestBoards(string title, vector<vector<Tiles>>& t);
	void dcMines();
	void dcTiles();
	void resetTiles(int mines);
	int getTiles();
	int setDigitTracker();
	


};

