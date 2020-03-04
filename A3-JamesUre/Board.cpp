//**************************************************
//BOARD CLASS - HANDLES ALL PROPERTIES OF THE BOARD
//**************************************************

//inclusions / imports
#include "Board.h"
#include <random>
#include <time.h>
#include <ctime>
#include <fstream>

//default constructor
Board::Board() {
}

//constructs board based on difficulty
Board::Board(Difficulty difficulty) {
	switch (difficulty) {

		//sets board properties based on difficulty selected
	case BEGINNER:
		difficultyMessage = "BEGINNER - 2 rows - Pieces: Y, B, G, P";
		tileDiff = 4;
		boardWidth = 2;
		break;
	case EASY:
		difficultyMessage = "EASY - 3 rows - Pieces: Y, B, G, P, C";
		tileDiff = 5;
		boardWidth = 3;
		break;
	case MEDIUM:
		difficultyMessage = "MEDIUM - 4 rows - Pieces: Y, B, G, P, C, O";
		tileDiff = 6;
		boardWidth = 4;
		break;
	case HARD:
		difficultyMessage = "HARD - 5 rows - Pieces: Y, B, G, P, C, O, R";
		tileDiff = 7;
		boardWidth = 5;
		break;
	case INSANE:
		difficultyMessage = "INSANE - 6 rows - Pieces: Y, B, G, P, C, O, R, M";
		tileDiff = 8;
		boardWidth = 6;
		break;
	}

	//properties of board regardless of difficulty
	codeRow.resize(10);
	resultRows.resize(10);

	//sets vectors of board
	for (int i = 0; i < 10; i++) {
		codeRow[i].resize(boardWidth, ' ');
		resultRows[i].resize(boardWidth, ' ');
	}

	//rest of the vectors board holds, secret and latest move
	secret.resize(boardWidth, ' ');
	latestRow.resize(boardWidth, ' ');
	genRandomCode(boardWidth);
}

//destructor
Board::~Board() {

}

//gives a user interface of the state of the board currently
string Board::displayBoard() {
	stringstream boardDetails;
	boardDetails << difficultyMessage << "\n";
	for (int rowInc = 0; rowInc < 10; rowInc++) {
		boardDetails << "-";
		for (int i = 0; i < boardWidth; i++) {
			boardDetails << "----";
		}
		boardDetails << "     -";
		for (int i = 0; i < boardWidth; i++) {
			boardDetails << "----";
		}
		boardDetails << "\n";
		boardDetails << "| ";
		for (int codeInc = 0; codeInc < boardWidth; codeInc++) {

			boardDetails << codeRow[9 - rowInc][codeInc] << " | ";

		}
		boardDetails << "===";
		boardDetails << " | ";
		for (int resultInc = 0; resultInc < boardWidth; resultInc++) {
			boardDetails << resultRows[9 - rowInc][resultInc] << " | ";
		}
		boardDetails << "\n";
	}
	boardDetails << "-";
	for (int i = 0; i < boardWidth; i++) {
		boardDetails << "----";
	}
	boardDetails << "     -";
	for (int i = 0; i < boardWidth; i++) {
		boardDetails << "----";
	}
	boardDetails << "\n";
	return boardDetails.str();
}

//sets a move into the board then increments the move count by 1
void Board::setBoard(vector<char> &playerMove) {
	for (int i = 0; i < boardWidth; i++) {
		codeRow[currentMove][i] = playerMove[i];
	}
	currentMove += 1;
}

//returns a pointer to the latest move 
vector<char>* Board::getLatestMove() {
	vector<char>* ptrMove = &codeRow[currentMove - 1];
	return ptrMove;
}

//the vector results was made in the move class, this will be inserted into the results 
//grid on the board
void Board::setResults(vector<char> &results) {

	for (int i = 0; i < boardWidth; i++) {
		resultRows[currentMove - 1][i] = results[i];
	}
}

//returns a pointer to the latest results
vector<char>* Board::getResults() {
	vector<char>* ptrResults = &resultRows[currentMove - 1];
	return ptrResults;
}

//returns a pointer to the secret code
vector<char>* Board::getSecret() {
	vector<char>* ptrSecret = &secret;
	return ptrSecret;
}

//returns the int containing the current move of the board
int Board::getCurrentMove() {
	return currentMove;
}

//returns the width of the board
int Board::getBoardWidth() {
	return boardWidth;
}

//makes the random code
void Board::genRandomCode(int length) {
	//because seeds default to same value upon program initialization
	//using timer to further randomize value
	srand(time(NULL));

	//sets random tiles onto secret grid
	for (int i = 0; i < length; i++) {
		secret[i] = letterTiles[rand() % tileDiff];
	}
}

//checks to see whether latest move matches secret code
bool Board::checkWin() {
	for (int i = 0; i < boardWidth; i++) {
		if ((*getLatestMove())[i] != secret[i]) {
			return false;
		}
	}
	return true;
}

//checks to see if player has exceeded number of attempts
bool Board::checkLose() {
	if (currentMove > 9) {
		return true;
	}
	return false;
}

//refreshes board with empty grids
void Board::clearBoard() {
	for (int i = 0; i < 10; i++) {
		fill(codeRow[i].begin(), codeRow[i].end(), ' ');
		fill(resultRows[i].begin(), resultRows[i].end(), ' ');
	}
}

//checks to see if a users move exists in existing tile options on board
bool Board::isValidMove(char userinput) {
	for (int i = 0; i < tileDiff; i++) {
		if (userinput == letterTiles[i]) {
			return true;
		}
	}
	return false;
}

//SAVES ALL BOARD DATA ONTO 2 FILES
void Board::saveBoard() {

	//will be written into file boardsave.txt
	stringstream saveData;

	//SAVES ALL BOARD PROPERTIES INTO BOARDSAVE.TXT
	saveData << tileDiff << "\n" << difficultyMessage << "\n" << currentMove << "\n" << boardWidth << "\n";

	try {
		ofstream file;

		//puts it into the boardsave.txt file then closes
		file.open("boardSave.txt", fstream::out);
		file << saveData.str();
		file.close();
	}
	//just incase of c++ black magic
	catch (exception) {
		cout << "filename doesnt exist";
	}

	//will be written into file gridsave.txt
	stringstream saveData2;

	//looping through all vectors and spacing them in a specific format for file
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < boardWidth; j++) {
			saveData2 << codeRow[i][j];
		}
		saveData2 << "\n";
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < boardWidth; j++) {
			saveData2 << resultRows[i][j];
		}
		saveData2 << "\n";
	}
	for (int i = 0; i < boardWidth; i++) {
		saveData2 << secret[i];
	}

	try {
		ofstream file;

		//puts it into the gridsave file then closes
		file.open("gridSave.txt", fstream::out);
		file << saveData2.str();
		file.close();
	}
	catch (exception) {
		cout << "filename doesnt exist";
	}

}

//LOADS BOARD DATA FROM 2 FILES
void Board::loadBoard() {

	//loads all data from boardsave.txt into appropriate board attributes
	ifstream file;
	file.open("boardSave.txt", fstream::out);
	string currentline = "";
	getline(file, currentline);
	tileDiff = stoi(currentline);

	getline(file, difficultyMessage);
	getline(file, currentline);
	currentMove = stoi(currentline);
	getline(file, currentline);
	boardWidth = stoi(currentline);

	file.close();

	//loads all data from gridsave.txt into appropriate vectors of board
	file.open("gridSave.txt", fstream::out);

	//resizes vectors to handle inputting from file
	codeRow.resize(10);
	resultRows.resize(10);
	secret.resize(boardWidth);

	//sets each row of the code and result grid to the width of the board
	for (int i = 0; i < 10; i++) {
		codeRow[i].resize(boardWidth, ' ');
		resultRows[i].resize(boardWidth, ' ');
	}

	//inputs users code from file
	for (int i = 0; i < 10; i++) {
		getline(file, currentline);
		for (int j = 0; j < boardWidth; j++) {
			if (currentline[j] != '\n') {
				codeRow[i][j] = currentline[j];
			}
		}
	}

	//input result code from file
	for (int i = 0; i < 10; i++) {
		getline(file, currentline);
		for (int j = 0; j < boardWidth; j++) {
			if (currentline[j] != '\n') {
				resultRows[i][j] = currentline[j];
			}
		}
	}

	//input secret code from file
	getline(file, currentline);
	for (int i = 0; i < boardWidth; i++) {
		if (currentline[i] != '\n') {
			secret[i] = currentline[i];
		}
	}
}