/**************************************                                        
*	Name: Nate Rupsis				  *
*	Date: 10/24/2015    			  *
*	Lab: 	Final			          *
*	File: 	Rupsis_Final.txt	      *
*   Course: CIS 2542-001           	  *
*	Description:Our Final Program is  *
*   Battle Ship. It provides the user *
*	all the fun of the physical game, *
*	but no need for human interaction.*
***************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <windows.h>					   // Console BackGround color
WORD Attributes = 0;


using namespace std;

ofstream ofs("Rupsis_final.txt");
std::ifstream ifs("Rupsis_batttle-ship-rules.txt"); // input file 

vector <string> rules;
string input;
int rulesIndex = 0;

/*
* Function, Reads the file into a vector
*/
void readInFile(){
	while(!ifs.eof()){
			getline(ifs, input);
			rules.push_back(input);
			rulesIndex++;
		}
	}
/*
* Console Color Function.
*/
void SetConsoleColour(WORD* Attributes, DWORD Colour){
	CONSOLE_SCREEN_BUFFER_INFO Info;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &Info);
	*Attributes = Info.wAttributes;
	SetConsoleTextAttribute(hStdout, Colour);
}

void ResetConsoleColour(WORD Attributes){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}



/**************************************
*	Global Style Variables 			  *
***************************************/
	string nl = "\n"; //new line
	string slash = "/";
	string s = " ";
	string cs = ", ";
	string ls = "| "; // line space
	string sl = " |"; // space line 
	string sls =" | "; // space line space
	string lss = "|  ";
	char stars = '*';
	char dashes ='-';
	string times = " * ";
	string equals = " = ";
	string s5 = "     ";
	string s3 = "   ";
	char ship = 254;
	char shipHit = 'X';
	char shipMiss = '0';

	
	string alphaError = "Error! please enter a valid numerical date";
	
/**************************************
*   Global Function Variables         *
***************************************/
// Function Vars
string header = " Midterm "; // Header Title
string description1=" "; // description 1
string description2 = " ";// description 2

// EOF + Footer Vars 
string no = "EOF MESSAGE "; // EOF Title
string hard = "Nate Rupsis "; // name
string coding = " October 25 2015 "; //date
string of = " Midterm "; // title
string labn = " Midterm "; // lab number
string anything = "See ya "; //tag line
string course =" CIS 2542-001 ";

// Main Menu  
char numbersSide[] = {'0','1','2','3','4'};
char emptySpace = '-'; 
string equalsLine = "=================================================================";
string playerTitle = "|                      - Player's Screen-                       |";
string topAndBottom = "-+---------------------------+";
string gameBoardMiddle = "-|---+---+---+---+---+---+---|";
string lettersTop = " | 0 | 1 | 2 | 3 | 4 | 5 | 6 |      | 0 | 1 | 2 | 3 | 4 | 5 | 6 |";
string boardFooter = "|       Attack Screen        |     |       Defence Screen       |";
string boardGap = "     ";


string titleMenu[] = {"-----------------------------------------------------------------------------------",    
                    "|                                     |__                                         |",
                    "|                                     ||/                                         |",
                    "|                                     ---                                         |",
                    "|                                     / | [                                       |",
                    "|                              !      | |||                                       |",
                    "|                            _/|     _/|-++'                                      |", 
                    "|                        +  +--|    |--|--|_ |-                                   |",
                    "|                     { /|__|  |/>__|  |--- |||__/                                |",
                    "|                    +---------------___[}-_===_.'____                 />         |",
                    "|                ____`-' ||___-{]_| _[}-  |     |_[___]==--            []   _     |",
                    "| __..._____--==/___]_|__|_____________________________[___]==--____,------' .7   |",
                    "||     *      *     *       *      BATTLE    *     *      *     *     *  BB-61/   |",
                    "| [_____________________________________SHIP_________________________________|    |",
                    "-----------------------------------------------------------------------------------",
					"|========|  1. Play Game  |====|   2. Rules  |====|  0. Quit   |==================|",
					"-----------------------------------------------------------------------------------"};
					




string userInstructions = "Please select";
string choice1 = "1. Play Game";
string choice2 = "2. Rules";
string quit = "0. Quit";

// isPositive 
string errorNeg = "Error! Input Cannot Be negative!";
string tryAgain = "Please Try Again: ";
double num = 0;

string notInBounds = "error, not in bounds";
string shipInPath = "error there is a ship in your path";
string invalidShot = "Error, invalid shot";
string nameTurn = "'s Shot";
string alreadyGuessed = "Already Guessed There, try again: ";
string enterRowAndColumn ="Enter Row and Column:";
string colon = ": ";
string coutHit ="Hit!";
string coutMiss = "Miss!";
string errorInvalidGrid = "Error! Please enter valid grid units: ";
string startingRowAndColumn = "Enter ship's starting Row. I.e (4) and column I.e (3)";
string placeingShips = "Placing Ship: ";
string horizontalOrVertical ="(0)Horizonal or (1)Vertical? ";
string errorInvalidOrientation ="Error! Please enter only 0 or 1";
int playerHealth = 3;
int computerHealth = 3;
int playerHits = 0;
int playerMisses = 0;
int computerHits = 0;
int computerMisses = 0;



class Player{
	private:
		string name;
		int hits;
		int misses;
		int health;
		char attackScreen[5][7];
		char defenceScreen[5][7];
		char minesweeper[2]; // ■ ■
		char frigate[3]; // ■ ■ ■
		char cruiser[4]; // ■ ■ ■ ■
		char BattleShip[5];//
		
	// setters and getters.	
	public:
	void setName(string n){ name = n; }
	void setHealth(int h){ health = h;}
	int getHealth(){ return health;}
	
/*
* Sets a blank gameboard
*/	
	void setGameBoard(){
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 7; j++){
				attackScreen[i][j] = emptySpace;
				defenceScreen[i][j] = emptySpace;
			}
			
		}
	}

/*
* User Sets ships
*/	
	void userSetGamePieces(int shipNum, string shipName){
			int userOrientation;
			int userRow;
			int userColumn;
			bool isShipThere = false;
				system("CLS");
				displayGameBoard();
				cout << this->name << colon << endl;
				cout << placeingShips << shipName << endl;
				cout << horizontalOrVertical << endl;
				while(!(cin >> userOrientation)){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << alphaError <<endl;
				}
				while(((userOrientation != 0) && (userOrientation != 1))){
					
					cout << errorInvalidOrientation << endl;
					while(!(cin >> userOrientation)){
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << alphaError <<endl;
					}	
				}
				
				
				// TODO user error handeling 
				cout << startingRowAndColumn << endl;
				while(!(cin >> userRow)){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << alphaError <<endl;
				}
				while(!(cin >> userColumn)){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << alphaError <<endl;
				}
				
				while(validatePlacement(userRow, userColumn, userOrientation, shipNum) != 1){
					cout << errorInvalidGrid << endl;
					cin >> userRow;
					cin >> userColumn;
				}
				
	
				
			for(int i = 0; i < shipNum; i++){
			
				if(userOrientation == 0){
					if((userColumn + (shipNum)) <= 6){
						this->defenceScreen[userRow][userColumn + i] = ship;
					}else{
						this->defenceScreen[userRow][userColumn - i]= ship;
					}
				}else{
					if((userRow + (shipNum)) <= 4){
						this->defenceScreen[userRow + i][userColumn] = ship;
					}else{
						this->defenceScreen[userRow - i][userColumn] = ship;
					}
				}	
			}
		
			
			system("PAUSE");
	}

/*
* Computer Sets ships
*/		
	void computerSetGamePieces(int shipNum, string shipName){
			int compOrientation;
			int compRow;
			int compColumn;
			bool isShipThere = false;
				system("CLS");
				cout << this->name << colon << endl;
				cout << placeingShips  << shipName<< endl;
				
				compOrientation = rand() % 1; 
				while((compOrientation != 0) && (compOrientation != 1)){
					compOrientation = rand() % 1; 
				}
				// Random numbers are generated for computer
				compRow = rand() % 5; 
				compColumn = rand() % 7;
				
				while((compRow < 0 || compRow > 4) && (compColumn < 0 || compColumn > 6)){
						compRow = rand() % 5; 
						compColumn = rand() % 7;
				}
				
			for(int i = 0; i < shipNum; i++){
				if(compOrientation == 0){
					if((compColumn + (shipNum - 1 )) <= 6){
						this->defenceScreen[compRow][compColumn + i] = ship;
					}else{
						this->defenceScreen[compRow][compColumn - i]= ship;
					}
				}else{
					if((compRow + (shipNum - 1 )) <= 4){
						this->defenceScreen[compRow + i][compColumn] = ship;
					}else{
						this->defenceScreen[compRow - i][compColumn] = ship;
					}
				}	
			}
		
			
			system("PAUSE");
	}

/*
* Overloaded function for validating shipplacement
*/		
	int validatePlacement(int row, int column, int orientaion, int shipNum){
		
		if(((row < 0) || (row > 6)) && ((column < 0) || (column > 4)) ){
			cout << notInBounds;
			return -1;
		} 
		
		
		for(int i = 0; i < shipNum; i++){
			
				if(orientaion == 0){
					if(this->defenceScreen[row][column + i] == ship){ 
						cout << shipInPath << endl;
						return -1;
					}
				}else{
					if(this->defenceScreen[row + i][column] == ship){ 
						cout << shipInPath << endl;
						return -1;
					}
				}	
			}
		return 1;
	}

/*
* Overloaded function for validating shipplacement
*/	
	int validatePlacement(int row, int column, Player c){
		
		if(c.defenceScreen[row][column] == shipHit){
				cout << alreadyGuessed << endl;
				return -1;
			}else if(c.defenceScreen[row][column] == shipMiss){
				cout << alreadyGuessed << endl;
				return -1;
			}
		
		if(((row < 0) || (row > 6)) && ((column < 0) || (column > 4)) ){
			cout << notInBounds << endl;
			return -1;
		} 

		return 1;
	}

/*
* Displays the game board. Red = hit, Blue = miss
*/	
	void displayGameBoard(){
		cout << equalsLine << endl;
		cout << playerTitle << endl;
		cout << equalsLine << endl;
		cout << lettersTop << endl;

			cout << topAndBottom << "     " << topAndBottom << endl;
			for(int i = 0; i < 5; i++){
				cout << numbersSide[i] << ls;
				for(int j = 0; j < 7; j++){
					if(attackScreen[i][j] == shipHit){
						SetConsoleColour(&Attributes,BACKGROUND_INTENSITY | BACKGROUND_RED);
						cout << attackScreen[i][j];	
						ResetConsoleColour(Attributes);
						cout << sls;
					}else if(attackScreen[i][j] == shipMiss){
						SetConsoleColour(&Attributes,BACKGROUND_INTENSITY | BACKGROUND_BLUE);
						cout << attackScreen[i][j];	
						ResetConsoleColour(Attributes);
						cout << sls;
					}else{
					cout << attackScreen[i][j] << sls;
					}
				}
				cout << "    " << numbersSide[i] << ls;
				for(int j = 0; j < 7; j++){
					if(defenceScreen[i][j] == shipHit){
						SetConsoleColour(&Attributes,BACKGROUND_INTENSITY | BACKGROUND_RED);
						cout << defenceScreen[i][j];	
						ResetConsoleColour(Attributes);
						cout << sls;
					}else if(defenceScreen[i][j] == shipMiss){
						SetConsoleColour(&Attributes,BACKGROUND_INTENSITY | BACKGROUND_BLUE);
						cout << defenceScreen[i][j];	
						ResetConsoleColour(Attributes);
						cout << sls;
					}else{
					cout << defenceScreen[i][j] << sls;
					}
				}
				cout << endl;
				if(i < 4){
					cout << gameBoardMiddle << boardGap << gameBoardMiddle << endl;
				}
			}
			
			cout << topAndBottom << boardGap << topAndBottom << endl;
			cout << boardFooter << endl;
			cout << equalsLine << endl;
			
			
			
			
	}	

/*
* User Guess Function 
*/	
	void userGuess(Player c){
		int userRow;
		int userColumn;
		cout << this->name << nameTurn << endl;
		cout<< enterRowAndColumn << endl;
		while(!(cin >> userRow)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << alphaError <<endl;
			}
		while(!(cin >> userColumn)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << alphaError <<endl;
			}
		while((validatePlacement(userRow, userColumn, c) != 1)){
			cout << notInBounds << endl;
			cin >> userRow;
			cin >> userColumn;
		}
		
		
			if(c.defenceScreen[userRow][userColumn] == ship){
				cout << coutHit << endl;
				this->attackScreen[userRow][userColumn] = shipHit;
				computerHealth--;
				playerHits++;
			}else{
				cout << coutMiss << endl;
				this->attackScreen[userRow][userColumn] = shipMiss;
				playerMisses++;
			}
			
		
	}
/*
* Computer Guess Function 
*/	
	void computerGuess(Player c){
		int compRow;
		int compColumn;
		cout << c.name << nameTurn << endl;
		compRow = rand() % 5; 
		cout << compRow << endl;
		
		compColumn = rand() % 7;
		cout << compColumn << endl;
		
		while(((this->defenceScreen[compRow][compColumn] == shipHit)||(this->defenceScreen[compRow][compColumn] == shipMiss))){
			compRow = rand() % 5; 
			cout << compRow << endl;
			
			compColumn = rand() % 7;
			cout << compColumn << endl;
		}
		
		
		if(this->defenceScreen[compRow][compColumn] == ship){
			cout << coutHit << endl;
			this->defenceScreen[compRow][compColumn] = shipHit;
			playerHealth--;
			computerHits++;
		}else{
			cout << coutMiss << endl;
			this->defenceScreen[compRow][compColumn] = shipMiss;
			computerMisses++;
		}
			
		
		system("PAUSE");
	}

	
	
};

 
/**************************************
*	Global String Variables 		  *
***************************************/
	string goodBye = "Good Bye!"; 
	string line="-----------------------------";
	string invalidInput = "invalid input";

/**************************************
*	Function Prototypes 			  *
***************************************/
// Default Functions
void hdr();
void ftr();
void eof();
void blankLine();
void dashedLine();
void starLine();

void mainMenu();
void rulesMenu();
void gameMenu();
void setPlayersName();
void displayHealth(Player, Player );
void displayWinner();
void displayStats();



int validateInt();
double isPositive();

Player player;
Player computer;


/**************************************
*	Main Function. 					  *
***************************************/

int main(){
	readInFile();
	 mainMenu(); // main menu
	
     ftr(); // Footer 
     eof(); // End of File 
	return 0;
}

/*************************************************************
*Main Menu, User controlled menu to call different function  *
**************************************************************/
void mainMenu(){
	
int userInput;
do {
	for(int i = 0; i < 17; i++){
		system("COLOR 0C");
		cout << titleMenu[i] << endl;
	}
	
	userInput = validateInt();
			switch(userInput){
				case 0:
					cout << goodBye << endl;
					break;
				case 1:
					 gameMenu();
					break;
				case 2:
					rulesMenu();
					break;
				case 3:
	
					break;
				default:
					cout << invalidInput << endl;
			}
	}while(userInput != 0);
}
/*
* game menu.
*/
void gameMenu(){
	system("CLS");
	system("COLOR 0A");
	
	setPlayersName();
	
	playerHealth = 5;
	computerHealth = 5;
	
	// sets the gameboard, and the player/computer ships
	player.setGameBoard();
	player.userSetGamePieces(2, "Minesweeper (2)");
	player.userSetGamePieces(3, "Frigate (3)");
	//player.userSetGamePieces(4, "Cruiser (4)");  // to keep demo short, only 2 ship. 
	
	computer.computerSetGamePieces(2, "Minesweeper (2)");
	computer.computerSetGamePieces(3, "Frigate (3)");
	//computer.computerSetGamePieces(4, "Cruiser (4)"); 

	
	while((playerHealth > 0) && (computerHealth > 0)){
		system("CLS");
		player.displayGameBoard(); // prints board
		displayHealth(player, computer); // displays health
		player.userGuess(computer); // user shot
		player.computerGuess(computer); // computer shot

		system("PAUSE");
		 
	}
	displayWinner();
	displayStats();
	system("PAUSE");
}

/*
* Rules Menu 
*/
void rulesMenu(){
	system("CLS");
	system("COLOR 0B");
		for(int i = 0; i < rulesIndex; i++ ){
			
			cout << ls << left << setw(76) << rules[i] << sl << endl;
		}
	system("PAUSE");
	system("CLS");
	
}

/*
* sets Players name
*/
void setPlayersName(){
	string userName;
	string computerName;
	string enterPlayerName = "Please Enter your name: ";
	string enterCompName ="Please Computer name: ";
	system("CLS");
	system("COLOR 0B");
	cout << enterPlayerName << endl;
	cin >> userName;
	player.setName(userName);
	
	cout << enterCompName << endl;
	cin >> computerName;
	computer.setName(computerName);
	system("PAUSE");
	
}

/*
* Displays Players Health status
*/
void displayHealth(Player p, Player c){
	string disPlayerHealth ="PlayerHealth: ";
	string disCompHealth =" ComputerHealh: ";
		cout << disPlayerHealth  << playerHealth << disCompHealth << computerHealth << endl;
		cout << endl;
	}

/*
* Displays Winner 
*/
void displayWinner(){
	string youWin = "You win!";
	string youLose = "You Lose... :/ ";
	system("CLS");
	if(playerHealth > computerHealth){
		cout << youWin << endl;
	}else{
		cout << youLose << endl;
	}
	system("PAUSE");
}

/*
* Displays Stats
*/

void displayStats(){
	
	string disPlayerHits = "Player's Hits: ";
	string disCompHits = "Computer's Hits: ";
	string disMisses = " Misses: ";
	string stats = "Game Stats";
	system("CLS");
	cout << stats << endl;
	cout << disPlayerHits << playerHits << disMisses << playerMisses << endl;
	cout << disCompHits << computerHits << disMisses << computerMisses << endl;
	system("Pause");
}

/*********************************************
*int Validate. Checks to see if alphabetical *
* data is entered and throws error			 *
**********************************************/
int validateInt(){
	int userInt;
	while(!(cin >> userInt)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << alphaError <<endl;
		}
	return userInt;
}


/**************************************
*	Style Functions 				  *
***************************************/
void blankLine(){
	ofs << ls << setfill(' ') << right << setw(76) << sl << endl;
}

void dashedLine(){
	ofs << ls << setfill(dashes) << right << setw(76) << sl <<  setfill(' ') << endl;
}

void starLine(){
	ofs << ls << setfill(stars) << right << setw(76) << sl << setfill(' ') << endl;
}


/**************************************
*	Header  function				  *
***************************************/
void hdr(){
    starLine();
    ofs << ls <<setfill(' ') << right << setw(39) << header << right << setw(37) << sl << endl;
    starLine();
  //  blankLine();
  //  ofs << ls << left << setw(74) << description1 << sl << endl;
  // ofs << ls << left << setw(74)<< description2 << setw(59)<< sl<< endl;
  //  blankLine();

}


/**************************************
*	Footer function					  *
***************************************/
void ftr(){
	//Footer
	blankLine();
	dashedLine();
	ofs << ls << right << setw(21) << hard << coding << labn << course << right <<  setw(15) << sl << endl;										  
} 


/**************************************
*	End of File function			  *
***************************************/
void eof(){

	// EOF MEssage 
	
	dashedLine();
	ofs << ls << right << setw(21) << no << hard << coding << labn  << anything << right << setw(10) << sl <<endl;
	dashedLine();

	 //closes fstream 
	ofs.close();										  
} 

