//**************
//PLAYER HEADER
//**************

//inclusions / imports
#include <string>
#include <iostream>
#include "enum.h"
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
	//name related
	string playerName;

	//score related
	int playerScore;
	int totalScore = 0;

	//attempts related
	int playerAttempts;

	//games related
	int playerGames;
	int playerGamesWon;

	//rank related
	int promotionTally = 0;
	int demotionTally = 0;
	Rank rank;


public:
	string displayRank;
	//constructors & destructors
	Player();
	Player(string newName, int newAttempts, int newScore, int newGames, int newWins);
	~Player();

	//name related
	string getName();
	void setName(string newName);

	//score related
	int getScore();
	void updateScore(int newScore);
	void setScore(int newScore);
	void updateTotalScore();
	int getTotalScore();

	//attempt related
	int getAttempts();
	void updateAttempts(int newAttempts);
	void resetAttempts(int newAttempts);

	//game related
	void updateGames(int gamesPlayed);
	void updateWins(int winsGained);
	int getGames();
	int getWins();

	//rank related
	void updateRank(bool win);
	void promotion();
	void demotion();

	//save
	void savePlayer();
	void loadPlayer();

	//for user interface
	string printPlayer();
};
#endif