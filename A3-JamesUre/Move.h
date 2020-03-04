//************
//MOVE HEADER
//************

//inclusions / imports
#include "Board.h"

#ifndef MOVE_H
#define MOVE_H
class Move {
private:
	//players inserted code
	vector<char> playerMove;

	//secret code to check against
	vector<char> secretCode;

	//returned feedback grid
	vector<char> feedback;

	//holds index of where to insert onto feedback grid
	int markFeed = 0;

public:
	//constructors / destructors
	Move();
	~Move();

	//checks move vector against secret code vector
	void compareCode(vector<char> move, vector<char> code);

	//returns feedback grid generated
	vector<char>* getResults();
};
#endif
