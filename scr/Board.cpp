#include "Board.h"
#include "Tiles.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

Board::Board() {
	width = 0;
	height = 0;
	numOfMines = 0;
    numOfTiles = 0;
}
Board::Board(int width, int height, int mines) {
	this->width = width;
	this->height = height;
	this->numOfMines = mines;
    numOfTiles = (width * height) - numOfMines;
}

int Board::GetWidth(){
	return width;
}

int Board::GetHeight() {
	return height;
}

int Board::GetMines() {
	return numOfMines;
}
void Board::dcMines() {
    this->numOfMines--;
}

void Board::dcTiles() {
    this->numOfTiles--;
}
void Board::resetTiles(int mines) {
    numOfMines = mines;
    numOfTiles = (width * height) - numOfMines;
}

int Board::getTiles() {
    return numOfTiles;
}

int Board::MinesCloseBy(vector<vector<Tiles>>& t, int x, int y) {
    int numMines = 0;
   if (x != 0) {
       if (t[x - 1][y].getMineState()) {
           numMines++;
       }
   
       if (y != 0) {
           if (t[x - 1][y - 1].getMineState()) {
               numMines++;
           }
           if (t[x][y - 1].getMineState()) {
               numMines++;
           }
       }
   
       if (y != height - 1) {
           if (t[x - 1][y + 1].getMineState()) {
               numMines++;
           }
       }
   }
   if (y != 0) {
       if (x != width - 1) {
           if (t[x + 1][y - 1].getMineState()) {
               numMines++;
           }
       }
   }
   
   if (x != width - 1) {
       if (t[x + 1][y].getMineState()) {
           numMines++;
       }
   
       if (y != height - 1) {
           if (t[x + 1][y + 1].getMineState()) {
               numMines++;
           }
           if (t[x][y + 1].getMineState()) {
               numMines++;
           }
       }
   }
    return numMines;
}

int Board::setDigitTracker() {
    return numOfMines;
}

void Board::RecursiveReveal(vector<vector<Tiles>>& t, int x, int y) {
    int num = MinesCloseBy(t, x, y);

    if (!t[x][y].getRevealedState() && !t[x][y].getFlaggedState()) {
        t[x][y].setRevealed(true);
        dcTiles();
    }

    if (num == 0) {
        if (x != 0) {
            if (!t[x - 1][y].getMineState()) {
                if (!t[x - 1][y].getRevealedState()) {
                    RecursiveReveal(t, x - 1, y);
                }
            }

            if (y != 0) {
                if (!t[x - 1][y - 1].getMineState()) {
                    if (!t[x - 1][y - 1].getRevealedState()) {
                        RecursiveReveal(t, x - 1, y - 1);
                    }
                }
                if (!t[x][y - 1].getMineState()) {
                    if (!t[x][y - 1].getRevealedState()) {
                        RecursiveReveal(t, x, y - 1);
                    }
                }
            }

            if (y != height - 1) {
                if (!t[x - 1][y + 1].getMineState()) {
                    if (!t[x - 1][y + 1].getRevealedState()) {
                        RecursiveReveal(t, x - 1, y + 1);
                    }
                }
            }
        }
        if (y != 0) {
            if (x != width - 1) {
                if (!t[x + 1][y - 1].getMineState()) {
                    if (!t[x + 1][y - 1].getRevealedState()) {
                        RecursiveReveal(t, x + 1, y - 1);
                    }
                }
            }
        }

        if (x != width - 1) {
            if (!t[x + 1][y].getMineState()) {
                if (!t[x + 1][y].getRevealedState()) {
                    RecursiveReveal(t, x + 1, y);
                }
            }

            if (y != height - 1) {
                if (!t[x + 1][y + 1].getMineState()) {
                    if (!t[x + 1][y + 1].getRevealedState()) {
                        RecursiveReveal(t, x + 1, y + 1);
                    }
                }
                if (!t[x][y + 1].getMineState()) {
                    if (!t[x][y + 1].getRevealedState()) {
                        RecursiveReveal(t, x, y + 1);
                    }
                }
            }
        }
    
    }
    
}
void Board::TestBoards(string title, vector<vector<Tiles>>& t) {
    
    ifstream inFile(title);
    string line;
    int mineCounter = 0;
    

    if (inFile.is_open()) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                char temp;
                inFile >> temp;

                if (temp == '1') {
                    mineCounter++;
                    t[j][i].setMined(true);
                }
                else {
                    t[j][i].setMined(false);
                }

                t[j][i].setRevealed(false);
                t[j][i].setFlagged(false);
            }
        }
        resetTiles(mineCounter);
    }
    inFile.close();
}