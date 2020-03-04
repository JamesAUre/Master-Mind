//*************************************
//EXTRA CLASS: MOVE CLASS
//Handles all decision making for
//feedback necessary on each given move
//*************************************

//inclusions / imports
#include "Move.h"

//constructor
Move::Move() {

}

//destructor
Move::~Move() {

}

//compares given move vector to code vector and saves results in local vector
void Move::compareCode(vector<char> move, vector<char> code) {
	int red = 0;
	int white = 0;
	feedback.resize(move.size(), ' ');
	vector<bool> redMatch(move.size(), false);
	vector<bool> whiteMatch(move.size(), false);

	//inserts red tiles
	for (int i = 0; i < move.size(); i++) {
		if (move[i] == code[i]) {
			redMatch[i] = true;
			whiteMatch[i] = true;
			red++;
		}
	}

	//inserts white tiles
	for (int i = 0; i < move.size(); i++) {
		if (redMatch[i] == false) {
			for (int j = 0; j < move.size(); j++) {
				if (i != j && redMatch[j] == false) {
					if (move[i] == code[j]) {
						whiteMatch[j] = true;
						white++;
					}
				}
			}
		}
	}

	//puts in all reds onto vector
	for (int redLoop = 0; redLoop < red; redLoop++) {
		feedback[markFeed] = 'R';
		markFeed++;
	}

	//puts in all whites onto vector
	for (int whiteLoop = 0; whiteLoop < white; whiteLoop++) {
		feedback[markFeed] = 'W';
		markFeed++;
	}
}

//returns a pointer to the results of the given move
vector<char>* Move::getResults() {
	vector<char>* ptrResults = &feedback;
	return ptrResults;
}
