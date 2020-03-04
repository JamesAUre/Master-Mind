//***************************************
//PROGRAM CREATED BY JAMES URE
//FINISHED ON 10/21/2019
//FIT 1048 MASTER MIND ASSIGNMENT 3
//***************************************

//inclusions / imports
#include "MasterMind.h"

//main function
int main() {
	intro();
	return 0;
}

//introducing user to games interface
void intro() {

	//reserved variable for input
	char userinput = ' ';

	//loops until user wishes to play (can be either new or a load)
	while (userinput != 'P' && userinput != 'L') {
		system("cls");
		displayText("intro");
		cout << "[R]ules\n"
			"[P]lay\n"
			"[L]oad existing game\n"
			"Select option: ";

		//handling userinput
		cin >> userinput;
		userinput = toupper(userinput);

		//displays rules from rules.txt
		if (userinput == 'R') {
			displayText("rules");
			system("pause");
		}

		//quit condition
		else if (userinput == 'Q') {
			return;
		}
	}

	//initializes game from save
	if (userinput == 'L') {
		Player player1 = Player();
		Board board = Board();

		//function will load save data into player1 and board objects
		saveCheck(player1, board, userinput);

		//checks if user saved after game end
		if (board.getCurrentMove() > 0) {
			if (board.checkWin() || board.checkLose()) {
				gameEnd(board, player1);
			}
		}

		//otherwise just resume game normally!
		MainGame(player1, board);

	}

	//initializes new game
	else {
		//sets up player profile in user setup
		Player player1 = userSetup();

		//sets up board from board setup (where user chooses difficulty)
		Board board = boardSetup();

		//start game!
		MainGame(player1, board);
	}
}

//initialize the player profile
Player userSetup() {
	string userName;
	cout << "Enter your name: ";
	cin >> userName;
	Player player1 = Player(userName, 0, 0, 0, 0);

	//pass the object of the player profile back
	return player1;
}

//contains the backbone loop of the game
void MainGame(Player& player, Board& board) {
	do {

		//gives interactive user interface that updates after each game cycle
		system("cls");
		cout << player.printPlayer() << endl;
		cout << board.displayBoard() << endl;

		//handles user input
		makeMove(board, player);

		//checks to see if game should continue or end
	} while (!board.checkLose() && !board.checkWin());

	//once loop ends, game cycle finished
	gameEnd(board, player);
}

//feedback to user once game ends
void gameEnd(Board& board, Player& player) {
	system("cls");

	//if the player won
	if (board.checkWin()) {
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
			"Congratulations " << player.getName() << ", you diffused the bomb!\n"
			"Score: " << player.getScore() << "\n"
			"Total score: " << player.getTotalScore() << "\n"
			"~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

		//updates the players progress towards a promotion! (needs 3 in a row)
		player.updateRank(true);
		system("pause");
	}

	//if the player lost
	else if (board.checkLose()) {
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
			"Oh no, you failed!\n"
			"Score: " << player.getScore() << "\n"
			"Total score: " << player.getTotalScore() << "\n"
			"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

		//updates the players progress towards a demotion! (needs 3 in a row)
		player.updateRank(false);
		system("pause");
	}

	//allows user to make decision on what to do from here
	endOptions(player, board);

}

//gives user the option for what to do next after a game ends
void endOptions(Player& player, Board& board) {

	//char reserved for user input
	char userinput = ' ';

	//loops until user gives valid input to break it
	while (userinput != 'P' && userinput != 'Q' && userinput != 'L') {
		cout << "[P]lay again\n"
			<< "[Q]uit\n"
			<< "[L]oad from another save\n"
			<< "[S]ave progress\n"
			<< "Select option: ";

		//handles user input
		cin >> userinput;
		userinput = toupper(userinput);

		//checks if the user wishes to save or load and handles player and board objects accordingly
		saveCheck(player, board, userinput);
	}

	//updates player win count if they won
	if (board.checkWin()) {
		player.updateWins(1);
	}

	//updates all the players other stats after game finish
	player.updateTotalScore();
	player.setScore(0);
	player.updateGames(1);
	player.resetAttempts(0);

	//checks to see if load was from a game finish
	if (userinput == 'L') {
		if (board.getCurrentMove() > 0) {
			if (board.checkWin() || board.checkLose()) {
				gameEnd(board, player);

			}
		}
		//if not resume game
		MainGame(player, board);
	}

	//starts new game
	else if (userinput == 'P') {
		Board board = boardSetup();
		MainGame(player, board);
	}
}

//handles userinput for their moves
void makeMove(Board& board, Player& player) {

	//move instantiation declared
	Move currentMove = Move();

	//the vector that will be inserted into the board and processed by move object
	vector<char> move = {};

	//reserved for current user input
	char selectedMove = ' ';

	//loops through moves (depends on difficulty!)
	for (int i = 0; i < board.getBoardWidth(); i++) {
		selectedMove = ' ';
		do {
			//handles userinput
			cout << "Enter move " << i + 1 << ": ";
			cin >> selectedMove;
			selectedMove = toupper(selectedMove);

			//checks to see if user wishes to save / load
			saveCheck(player, board, selectedMove);

			//if user wishes to load, checks to see if its from a game end
			if (selectedMove == 'L') {
				if (board.getCurrentMove() > 0) {
					if (board.checkWin() || board.checkLose()) {
						gameEnd(board, player);
					}
				}

			}

			//quits if user types 'q' (not case sensitive)
			else if (selectedMove == 'Q') {
				_Exit(0);
			}
		} while (!board.isValidMove(selectedMove));
		//puts moves on vector
		move.push_back(selectedMove);
	}

	//sets move into board
	board.setBoard(move);

	//compares the entered move to the secret code and produces feedback
	currentMove.compareCode(move, *board.getSecret());

	//insert feedback onto board
	board.setResults(*currentMove.getResults());

	//handles score gained
	scoring(player, board);

	player.updateAttempts(1);
}

void displayText(string openFile) {
	//where all data in file will be stored
	string myData = "";

	//stores the file line by line
	string line = "";

	ifstream file;
	file.open(openFile + ".txt");

	//reads file line by line
	if (file.is_open()) {
		while (getline(file, line)) {
			myData = myData + line + "\n";
		}
		file.close();
	}
	//prints data
	system("cls");
	cout << myData << endl;
}

//sets board based on difficulty
Board boardSetup() {

	//char reserved for user input
	char userinput = ' ';
	cout << "[B]eginner\n"
		<< "[E]asy\n"
		<< "[M]edium\n"
		<< "[H]ard\n"
		<< "[I]nsane\n";

	//loops until input is valid
	while (userinput != 'B' && userinput != 'E' && userinput != 'M' && userinput != 'H' && userinput != 'I') {

		//handles user input
		cout << "Select difficulty: ";
		cin >> userinput;
		userinput = toupper(userinput);

		//quits if userinput is 'q'
		if (userinput == 'Q') {
			_Exit(0);
		}

	}

	//creates board based on difficulty selected and returns it as created board
	if (userinput == 'B') {
		Board board = Board(BEGINNER);
		return board;
	}
	else if (userinput == 'E') {
		Board board = Board(EASY);
		return board;
	}
	else if (userinput == 'M') {
		Board board = Board(MEDIUM);
		return board;
	}
	else if (userinput == 'H') {
		Board board = Board(HARD);
		return board;
	}
	else if (userinput == 'I') {
		Board board = Board(INSANE);
		return board;
	}
}

//function for handling score
void scoring(Player& player, Board& board) {
	//final score
	int calculatingScore = 0;

	//score for red tiles
	int redTally = 0;

	//score for white tiles
	int whiteTally = 0;

	//gets all the red and white tiles from recent feedback grid
	for (int i = 0; i < board.getBoardWidth(); i++) {
		if ((*board.getResults())[i] == 'R') {
			redTally++;
		}
		else if ((*board.getResults())[i] == 'W') {
			whiteTally++;
		}
	}

	//calculates appropriate score based on feedback
	calculatingScore = (10 - player.getAttempts())*((redTally * 2) + (whiteTally));

	//updates player score based on score achieved
	player.updateScore(calculatingScore);
}

//does all the checking for saves / loads
void saveCheck(Player &player, Board &board, char &userinput) {

	//handles saves
	if (userinput == 'S') {

		//saves player
		player.savePlayer();

		//saves board
		board.saveBoard();
		cout << "data saved successfully!" << endl;
	}

	//handles loads
	else if (userinput == 'L') {

		//loads player
		player.loadPlayer();

		//loads board
		board.loadBoard();

		system("cls");
		cout << player.printPlayer() << endl;
		cout << board.displayBoard() << endl;

		cout << "data loaded successfully!" << endl;
	}
}