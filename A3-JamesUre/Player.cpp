//*********************************************************
//PLAYER CLASS - HANDLES ALL PROPERTIES OF THE USER PROFILE
//*********************************************************

//inclusions / imports
#include "Player.h"
#include <sstream>
#include <fstream>

//default constructor
Player::Player() {

}

//constructor for a new player with given default values
Player::Player(string newName, int newAttempts, int newScore, int newGames, int newWins) {
	playerName = newName;
	playerAttempts = newAttempts;
	playerScore = newScore;
	playerGames = newGames;
	playerGamesWon = newWins;
	rank = IRON;
	displayRank = "Iron";
}

//destructor
Player::~Player() {

}

//returns player username
string Player::getName() {
	return playerName;
}

//changes player username
void Player::setName(string newName) {
	playerName = newName;
}

//returns players current score
int Player::getScore() {
	return playerScore;
}

//adds onto players score
void Player::updateScore(int newScore) {
	playerScore += newScore;
}

//resets players score to the specified one
void Player::setScore(int newScore) {
	playerScore = newScore;
}

//gets player attempt tally
int Player::getAttempts() {
	return playerAttempts;
}

//adds onto attempt tally by specified number
void Player::updateAttempts(int newAttempts) {
	playerAttempts += newAttempts;
}

//resets attempts to the specified one
void Player::resetAttempts(int newAttempts) {
	playerAttempts = newAttempts;
}

//updates number of games played by specified number
void Player::updateGames(int gamesPlayed) {
	playerGames += gamesPlayed;
}

//updates number of games won by specified number
void Player::updateWins(int gamesWon) {
	playerGamesWon += gamesWon;
}

//get number of games played
int Player::getGames() {
	return playerGames;
}

//gets number of games won
int Player::getWins() {
	return playerGamesWon;
}

//updates total score (carried across all games)
void Player::updateTotalScore() {
	totalScore += playerScore;
}

//gets total score
int Player::getTotalScore() {
	return totalScore;
}

//prints user profile
string Player::printPlayer() {

	stringstream userDetails;

	//setting onto stringstream
	userDetails << "---------------------------------------------\n";
	userDetails << " Username: " << playerName << "	|	Attempt: " << playerAttempts + 1 << "	|	Rank: " << displayRank << "\n";
	userDetails << " Score: " << playerScore << "		|	Won Score: " << totalScore << "\n";
	userDetails << " Games played: " << playerGames << "	|	Games won: " << playerGamesWon << "\n";
	userDetails << "---------------------------------------------" << endl;

	//return as a string
	return userDetails.str();
}

//saves players stats
void Player::savePlayer() {
	stringstream saveData;

	//putting all relevant variables onto a string stream
	saveData << playerName << "\n" << playerScore << "\n" << totalScore << "\n" << playerGames << "\n"
		<< playerGamesWon << "\n" << playerAttempts << "\n" << (int)rank << displayRank;
	try {
		ofstream file;

		//writing stringstream onto file
		file.open("playerSave.txt", fstream::out);
		file << saveData.str();
		file.close();
	}
	catch (exception) {
		cout << "filename doesnt exist";
	}
}

//loads player stats
void Player::loadPlayer() {
	ifstream file;
	file.open("playerSave.txt", fstream::out);

	//reads file line by line
	if (file.is_open()) {
		int numRank = 0;

		//loading each line of file into appropriate variables
		while (file >> playerName >> playerScore >> totalScore >> playerGames >>
			playerGamesWon >> playerAttempts >> numRank >> displayRank) {
		}

		//needs to recast value from file as rank as it was stored as an integer
		rank = Rank(numRank);
		file.close();
	}
}

//updates progress towards a players rank
void Player::updateRank(bool win) {

	//executed if the player won a game
	if (win) {
		promotionTally++;
		demotionTally = 0;

		//promotion condition
		if (promotionTally > 2) {
			cout << "You've been promoted!" << endl;
			promotion();
			promotionTally = 0;
		}
	}

	//executed if the player lost a game
	else {
		demotionTally++;
		promotionTally = 0;

		//demotion condition
		if (demotionTally > 2) {
			cout << "You've been demoted :(" << endl;
			demotion();
			demotionTally = 0;
		}
	}
}

//promotes a player up a rank
void Player::promotion() {
	switch (rank) {
	case IRON:
		rank = BRONZE;
		displayRank = "Bronze";
		break;
	case BRONZE:
		rank = SILVER;
		displayRank = "Silver";
		break;
	case SILVER:
		rank = GOLD;
		displayRank = "Gold";
		break;
	case GOLD:
		rank = PLATINUM;
		displayRank = "Platinum";
		break;
	case PLATINUM:
		rank = DIAMOND;
		displayRank = "Diamond";
		break;
	case DIAMOND:
		rank = CHALLENGER;
		displayRank = "CHALLENGER";
		break;
	}
}

//demotes a player down a rank
void Player::demotion() {
	switch (rank) {
	case BRONZE:
		rank = IRON;
		displayRank = "Iron";
		break;
	case SILVER:
		rank = BRONZE;
		displayRank = "Bronze";
		break;
	case GOLD:
		rank = SILVER;
		displayRank = "Silver";
		break;
	case PLATINUM:
		rank = GOLD;
		displayRank = "Gold";
		break;
	case DIAMOND:
		rank = PLATINUM;
		displayRank = "Platinum";
		break;
	case CHALLENGER:
		rank = DIAMOND;
		displayRank = "Diamond";
		break;
	}
}