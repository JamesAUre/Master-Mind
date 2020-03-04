//*************
//BOARD HEADER
//*************

//inclusions / imports
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "enum.h"
using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board {
private:
	//tile related
	const char letterTiles[8] = { 'Y','B','G','P','C','O','R','M' };
	int tileDiff;

	//board vectors (2d)
	vector<vector<char> > codeRow;
	vector<vector<char> > resultRows;

	//board vectors (1d)
	vector<char> secret;
	vector<char> latestRow;

	//difficulty
	string difficultyMessage;
	Difficulty difficulty;

	//stores the move number of the game
	int currentMove = 0;
	int boardWidth;

public:

	//constructors / destructors
	Board();
	Board(Difficulty difficulty);
	~Board();

	//whole board 
	string displayBoard();
	void clearBoard();

	//results 
	void setResults(vector<char> &results);
	vector<char>* getResults();

	//secret code 
	void genRandomCode(int length);
	vector<char>* getSecret();

	//player move
	void setBoard(vector<char> &playerMove);
	vector<char>* getLatestMove();
	bool isValidMove(char userinput);

	//end conditions
	bool checkWin();
	bool checkLose();

	//save related
	void saveBoard();
	void loadBoard();

	//rest
	int getCurrentMove();
	int getBoardWidth();
};
#endif 
