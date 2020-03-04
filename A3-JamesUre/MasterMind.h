//**********************
//HEADER OF SOURCE FILE
//**********************

//inclusions / imports
#include "Player.h"
#include "Board.h"
#include "Move.h"
#include <string>
#include <fstream>

//function declarations
void makeMove(Board& board, Player& player);
void MainGame(Player& player, Board& board);
void intro();
void displayText(string openFile);
void gameEnd(Board& board, Player& player);
void scoring(Player& player, Board& board);
void saveCheck(Player& player, Board& board, char &userinput);
void endOptions(Player& player, Board& board);
Board boardSetup();
Player userSetup();
