#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Tiles.h"
#include "TextureManager.h"
#include "Random.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

Board& ReadConfig() {
    ifstream inFile("boards/config.cfg");
    int width;
    int height;
    int numOfMines;

    if (inFile.is_open()) {
        string temp;
        getline(inFile, temp);
        width = stoi(temp);

        getline(inFile, temp);
        height = stoi(temp);

        getline(inFile, temp);
        numOfMines = stoi(temp);

        Board b(width, height, numOfMines);
        return b;
    }
    inFile.close();
}
int main()
{
    sf::Sprite tileHidden(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite tileRevealed(TextureManager::GetTexture("tile_revealed"));
    sf::Sprite smiley(TextureManager::GetTexture("face_happy"));
    sf::Sprite faceLost(TextureManager::GetTexture("face_lose"));
    sf::Sprite faceWon(TextureManager::GetTexture("face_win"));
    sf::Sprite debugButton(TextureManager::GetTexture("debug"));
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    sf::Sprite digits(TextureManager::GetTexture("digits"));

    Tiles tile(tileHidden, tileRevealed, mine, flag, false, false, false);
    
    vector<Tiles> currentTiles;
    vector<vector<Tiles>> totalTiles;

    bool DebugOn = false;
    bool gameLost = false;
    bool gameWon = false;
    bool testCalled = false;
    bool neg = false;

    Board b = ReadConfig();

    int digitTracker = b.GetMines();

    // sets up vector<vector<Tiles>>
    for (int i = 0; i < b.GetWidth(); i++) {
        for (int j = 0; j < b.GetHeight(); j++) {
            currentTiles.push_back(tile);
        }
        totalTiles.push_back(currentTiles);
        currentTiles.clear();
    }

    // dividing up the nums in the digit counter
    map<string, sf::Sprite> digitSprites;
    sf::Vector2i size(21, 32);

    sf::Vector2i position0(0, 0);
    sf::Sprite num0 = tile.makeItRect(digits, position0, size);
    digitSprites.emplace("0", num0);

    sf::Vector2i position1(21, 0);
    sf::Sprite num1 = tile.makeItRect(digits, position1, size);
    digitSprites.emplace("1", num1);

    sf::Vector2i position2(42, 0);
    sf::Sprite num2 = tile.makeItRect(digits, position2, size);
    digitSprites.emplace("2", num2);

    sf::Vector2i position3(63, 0);
    sf::Sprite num3 = tile.makeItRect(digits, position3, size);
    digitSprites.emplace("3", num3);

    sf::Vector2i position4(84, 0);
    sf::Sprite num4 = tile.makeItRect(digits, position4, size);
    digitSprites.emplace("4", num4);

    sf::Vector2i position5(105, 0);
    sf::Sprite num5 = tile.makeItRect(digits, position5, size);
    digitSprites.emplace("5", num5);

    sf::Vector2i position6(126, 0);
    sf::Sprite num6 = tile.makeItRect(digits, position6, size);
    digitSprites.emplace("6", num6);

    sf::Vector2i position7(147, 0);
    sf::Sprite num7 = tile.makeItRect(digits, position7, size);
    digitSprites.emplace("7", num7);

    sf::Vector2i position8(168, 0);
    sf::Sprite num8 = tile.makeItRect(digits, position8, size);
    digitSprites.emplace("8", num8);

    sf::Vector2i position9(189, 0);
    sf::Sprite num9 = tile.makeItRect(digits, position9, size);
    digitSprites.emplace("9", num9);

    sf::Vector2i positionNeg(210, 0);
    sf::Sprite numNeg = tile.makeItRect(digits, positionNeg, size);
    digitSprites.emplace("-", numNeg);
  
    sf::RenderWindow window(sf::VideoMode(b.GetWidth()*32, (b.GetHeight()*32)+100), "Minesweeper");
    
    while (window.isOpen())
    {
        window.clear(sf::Color(255, 255, 255));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            

            // getting mines
            int mineCount = b.GetMines();

            while (mineCount > 0 && !testCalled) {

                int x = Random::Int(0, b.GetWidth() - 1);
                int y = Random::Int(0, b.GetHeight() - 1);

                if (!totalTiles[x][y].getMineState()) {
                    totalTiles[x][y].setMined(true);
                    b.dcMines();
                    mineCount = b.GetMines();
                }
            }
            
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                if (!gameLost && !gameWon) {
                    for (int i = 0; i < b.GetHeight(); i++) {
                        for (int j = 0; j < b.GetWidth(); j++) {
                            sf::FloatRect tileRect = totalTiles[j][i].getHidden().getGlobalBounds();
                            if (tileRect.contains(mousePosition.x, mousePosition.y)) {
                                bool temp = !totalTiles[j][i].getFlaggedState();
                                totalTiles[j][i].setFlagged(temp);

                                // to affect digit counter
                                if (temp == true) {
                                    digitTracker--;
                                }
                                else if (temp == false) {
                                    digitTracker++;
                                }
                            }
                        }
                    }
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // for reveal
                if (!gameLost && !gameWon) {
                    for (int i = 0; i < b.GetHeight(); i++) {
                        for (int j = 0; j < b.GetWidth(); j++) {
                            sf::FloatRect tileRect = totalTiles[j][i].getHidden().getGlobalBounds();
                            if (tileRect.contains(mousePosition.x, mousePosition.y)) {
                                if (totalTiles[j][i].getMineState()) {
                                    totalTiles[j][i].setRevealed(true);
                                    if (!totalTiles[j][i].getFlaggedState()) {
                                        gameLost = true;
                                    }
                                }
                                else {
                                    b.RecursiveReveal(totalTiles, j, i);
                                }
                            }
                        }
                    }
                    // for debug
                    sf::FloatRect debugRect = debugButton.getGlobalBounds();
                    if (debugRect.contains(mousePosition.x, mousePosition.y)) {
                        DebugOn = !DebugOn;
                    }
                }

                // resetting function 
                sf::FloatRect smileyRect = smiley.getGlobalBounds();
                if (smileyRect.contains(mousePosition.x, mousePosition.y)) {
                    for (int i = 0; i < b.GetWidth(); i++) {
                        for (int j = 0; j < b.GetHeight(); j++) {
                            totalTiles[i][j].setFlagged(false);
                            totalTiles[i][j].setMined(false);
                            totalTiles[i][j].setRevealed(false);
                        }
                    }
                    b = ReadConfig();
                    DebugOn = false;
                    gameLost = false;
                    gameWon = false;
                    b.resetTiles(b.GetMines());
                    testCalled = false;
                    digitTracker = b.setDigitTracker();
                    neg = false;
                }

                if (!gameLost && !gameWon) {
                    // test 1
                    sf::FloatRect test1Rect = test1.getGlobalBounds();
                    if (test1Rect.contains(mousePosition.x, mousePosition.y)) {
                        b.TestBoards("boards/testboard1.brd", totalTiles);
                        testCalled = true;
                        digitTracker = b.setDigitTracker();
                    }
                   

                    // test 2
                    sf::FloatRect test2Rect = test2.getGlobalBounds();
                    if (test2Rect.contains(mousePosition.x, mousePosition.y)) {
                        b.TestBoards("boards/testboard2.brd", totalTiles);
                        testCalled = true;
                        digitTracker = b.setDigitTracker();
                    }
                    

                    // test 3
                    sf::FloatRect test3Rect = test3.getGlobalBounds();
                    if (test3Rect.contains(mousePosition.x, mousePosition.y)) {
                        b.TestBoards("boards/testboard3.brd", totalTiles);
                        testCalled = true;
                        digitTracker = b.setDigitTracker();
                    }
                    
                }
            }

        }
        // if 0-9, if 10-99, if 100+

        string newDigitTracker = to_string(digitTracker);

        if (newDigitTracker.substr(0, 1) == "-") {
            digitSprites["-"].setPosition(0, b.GetHeight() * 32);
            window.draw(digitSprites["-"]);
            neg = true;

            newDigitTracker = newDigitTracker.substr(1);
        }

        if (newDigitTracker.length() == 1) {
            for (auto iter = digitSprites.begin(); iter != digitSprites.end(); iter++) {
                if (newDigitTracker == iter->first) {
                    if (neg) {
                        iter->second.setPosition(21, b.GetHeight() * 32);
                        window.draw(iter->second);
                    }
                    else {
                        iter->second.setPosition(0, b.GetHeight() * 32);
                        window.draw(iter->second);
                    }
                }
            }
        }
        if (newDigitTracker.length() == 2) {
            string temp1 = newDigitTracker.substr(0, 1);
            string temp2 = newDigitTracker.substr(1);

            sf::Sprite Stemp1;
            sf::Sprite Stemp2;

            for (auto iter = digitSprites.begin(); iter != digitSprites.end(); iter++) {
                if (temp1 == iter->first) {
                    
                    Stemp1 = iter->second;
                }
                if (temp2 == iter->first) {
                    
                    Stemp2 = iter->second;
                }
            }

            if (neg) {
                Stemp1.setPosition(21, b.GetHeight() * 32);
                window.draw(Stemp1);
                Stemp2.setPosition(42, b.GetHeight() * 32);
                window.draw(Stemp2);
            }
            else {
                Stemp1.setPosition(0, b.GetHeight() * 32);
                window.draw(Stemp1);
                Stemp2.setPosition(21, b.GetHeight() * 32);
                window.draw(Stemp2);
            }

        }
        if (newDigitTracker.length() == 3) {
            string temp1 = newDigitTracker.substr(0, 1);
            string temp2 = newDigitTracker.substr(1, 1);
            string temp3 = newDigitTracker.substr(2);

            sf::Sprite Stemp1;
            sf::Sprite Stemp2;
            sf::Sprite Stemp3;
           
            for (auto iter = digitSprites.begin(); iter != digitSprites.end(); iter++) {
                if (temp1 == iter->first) {
                    
                    Stemp1 = iter->second;
                }
                if (temp2 == iter->first) {
                    
                    Stemp2 = iter->second;
                }
                if (temp3 == iter->first) {
                    
                    Stemp3 = iter->second;
                }
            }
            if (neg) {
                Stemp1.setPosition(21, b.GetHeight() * 32);
                window.draw(Stemp1);
                Stemp2.setPosition(42, b.GetHeight() * 32);
                window.draw(Stemp2);
                Stemp3.setPosition(63, b.GetHeight() * 32);
                window.draw(Stemp3);
            }
            else {
                Stemp1.setPosition(0, b.GetHeight() * 32);
                window.draw(Stemp1);
                Stemp2.setPosition(21, b.GetHeight() * 32);
                window.draw(Stemp2);
                Stemp3.setPosition(42, b.GetHeight() * 32);
                window.draw(Stemp3);
            }
        }


        smiley.setPosition(((b.GetWidth() * 32) / 2) - 32, b.GetHeight() * 32);
        window.draw(smiley);


        debugButton.setPosition(((b.GetWidth() * 32) / 2) + 96, b.GetHeight() * 32);
        window.draw(debugButton);


        test1.setPosition((b.GetWidth() * 32) / 2 + 160, b.GetHeight() * 32);
        window.draw(test1);


        test2.setPosition((b.GetWidth() * 32) / 2 + 224, b.GetHeight() * 32);
        window.draw(test2);


        test3.setPosition((b.GetWidth() * 32) / 2 + 288, b.GetHeight() * 32);
        window.draw(test3);
       
        for (int i = 0; i < b.GetWidth(); i++) {
            for (int j = 0; j < b.GetHeight(); j++) {

                if (gameLost) {
                    faceLost.setPosition(((b.GetWidth() * 32) / 2) - 32, b.GetHeight() * 32);
                    window.draw(faceLost);

                    if (totalTiles[i][j].getMineState()) {
                        window.draw(totalTiles[i][j].getBomb());
                    }
                    
                }

                if (b.getTiles() == 0) {
                    gameWon = true;
                    faceWon.setPosition(((b.GetWidth() * 32) / 2) - 32, b.GetHeight() * 32);
                    window.draw(faceWon);

                    if (totalTiles[i][j].getMineState()) {
                        window.draw(totalTiles[i][j].getFlag());
                        digitTracker--; 

                    }
                }

                totalTiles[i][j].getRevealed().setPosition(i * 32, j * 32);
                window.draw(totalTiles[i][j].getRevealed());

                int num = b.MinesCloseBy(totalTiles, i, j);
                if (num != 0 && !totalTiles[i][j].getMineState()) {
                    totalTiles[i][j].setNum(num);
                    totalTiles[i][j].getNum().setPosition(i * 32, j * 32);
                }
        
                if (totalTiles[i][j].getRevealedState()) {
        
                    if (totalTiles[i][j].getMineState()) {
                        totalTiles[i][j].getBomb().setPosition(i * 32, j * 32);
                        window.draw(totalTiles[i][j].getBomb());
                    }
                    else {
                        if (num != 0) {
                            window.draw(totalTiles[i][j].getNum());
                        }
                    }
                }
                else {

                    totalTiles[i][j].getHidden().setPosition(i * 32, j * 32);
                    window.draw(totalTiles[i][j].getHidden());
        
                    if (totalTiles[i][j].getFlaggedState()) {
                        totalTiles[i][j].getFlag().setPosition(i * 32, j * 32);
                        window.draw(totalTiles[i][j].getFlag());
                    }

                    if (DebugOn) {
                        
                        if (totalTiles[i][j].getMineState()) {
                            totalTiles[i][j].getBomb().setPosition(i * 32, j * 32);
                            window.draw(totalTiles[i][j].getBomb());
                        }
                        
                    }
                }
            }
        }
        window.display();
    }
    TextureManager::Clear();

    return 0;
}