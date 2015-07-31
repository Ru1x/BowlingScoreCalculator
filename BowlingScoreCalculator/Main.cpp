/*
* Bowling Score Calculator
*
* Developed by herm1ne
*/

//-----Global Initialize-----
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
int NewScore(string x); //prototype declaration
bool IsInteger(const string& str);
int NofThrow();

//-----Declare G Variables-----
string sScore[21] = {}; //# of pins taken down (-1:N/A because of Spare or Strike -2:NotYet 0:Score is zero)
int iCurrentThrow = 1; //CurrentFrame (1 - 21)
string sScoreFrame[10] = {}; //Score thus far
string sMessage = "";

void initialize() {
	for (int i = 0; i < 21; i++) { //Initialize:(-2) Not yet
		sScore[i] = " ";
	}
	for (int i = 0; i < 10; i++) { //Initialize (   ) for blank output
		sScoreFrame[i] = "   ";
	}
	sMessage = "Let's start bowling!";
	return;
}

void calculate() {

}

void refresh() { //Just show the current sScore
	system("cls"); //Console Clear

	//output
	cout << "+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------+\n";
	cout << "|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |   10   |\n";
	cout << "+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+\n";
	cout << "| " + sScore[0] + "| " + sScore[1] + "| " + sScore[2] + "| " + sScore[3] + "| " + sScore[4] + "| " + sScore[5] + "| " + sScore[6] + "| " + sScore[7] + "| " + sScore[8] + "| " + sScore[9] + "| " + sScore[10] + "| " + sScore[11] + "| " + sScore[12] + "| " + sScore[13] + "| " + sScore[14] + "| " + sScore[15] + "| " + sScore[16] + "| " + sScore[17] + "| " + sScore[18] + "| " + sScore[19] + "| " + sScore[20] + "|\n";
	cout << "+  +--+  +--+  +--+  +--+  +--+  +--+  +--+  +--+  +--+--+--+--+\n";
	cout << "|  " + sScoreFrame[0] + "|  " + sScoreFrame[1] + "|  " + sScoreFrame[2] + "|  " + sScoreFrame[3] + "|  " + sScoreFrame[4] + "|  " + sScoreFrame[5] + "|  " + sScoreFrame[6] + "|  " + sScoreFrame[7] + "|  " + sScoreFrame[8] + "|     " + sScoreFrame[9] + "|\n";
	cout << "+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------+\n";
	//cout << sMessage + "\nPlese Enter the Score (Frame" + iCurrentThrow + ")\n";

	sMessage = "";
	return;
}


int main() //Main 
{
	string input;
	initialize();

	for (;iCurrentThrow <= 21; iCurrentThrow++) {
		for (int iReturnValue;;) {
			refresh();
			input = "";
			iReturnValue = -5;
			cin >> input;
			iReturnValue = NewScore(input);
			if (iReturnValue == 0) {
				break;
			}
			else if (iReturnValue == -1) {
				sMessage = "Invalid Value. Try again.";
				continue;
			}
			else if (iReturnValue == -2) {
				sMessage = "Exceed Max Value. Try again.";
				continue;
			}
			else if (iReturnValue == -3) {
				sMessage = "Strike cannot be in 2nd throw. Try again.";
				continue;
			}
			else if (iReturnValue == -4) {
				sMessage = "Spare cannot be in 1st throw. Try again.";
				continue;
			} else {
				sMessage = "Enter the score";
			}
			refresh();
		}
		refresh();
	}

	return 0;
}

/*
@fn
Convert typed sScore for output and insert into corresponding sScore[X]
@param (str) # of pins taken down
@return error code 0(no error) -1(Invalid Value) -2(Value excessed max sScore(10)) -999(Unexpected)
*/
int NewScore(string x) {
	//This chart is so complicated you can find table chart at :
	//TODO Upload table chart
	if (IsInteger(x) == true) { //IntegerSection
		if (stoi(x) == 10) {
			if (NofThrow() == 1) {
				sScore[iCurrentThrow - 1] = "X";
				return 0; //Result 1
			}
			else {
				if (sScore[iCurrentThrow - 2] == "G" || sScore[iCurrentThrow - 2] == "F" || sScore[iCurrentThrow - 2] == "-") {
					sScore[iCurrentThrow - 1] = "/";
					return 0; //Result 2
				}
				else {
					return -2; //Result 3
				}
			}
		}
		else if (stoi(x) == 0) {
			sScore[iCurrentThrow - 1] = "-";
			return 0; //Result 4
		}
		else if (1 <= stoi(x) && stoi(x) <= 9) {
			if (NofThrow() == 1) {
				sScore[iCurrentThrow - 1] = x;
				return 0; //Result 5
			}
			else {
				if (sScore[iCurrentThrow - 2] == "G" || sScore[iCurrentThrow - 2] == "F" || sScore[iCurrentThrow - 2] == "-") {
					sScore[iCurrentThrow - 1] = x;
					return 0; //Result 6
				}
				else if (iCurrentThrow >= 2 && stoi(sScore[iCurrentThrow - 2]) + stoi(x) > 10) { //TODO Problem/
					return -2; //Result 7 Exceed Max Score
				}
				else if (iCurrentThrow >= 2 && stoi(sScore[iCurrentThrow - 2]) + stoi(x) == 10) {
					sScore[iCurrentThrow - 1] = "/";
					return 0; //Result 8
				}
				else {
					sScore[iCurrentThrow - 1] = x;
					return 0; //Result 9
				}
			}
		}
		else { //Too Big or Too Small Number Entered!
			return -1; //Result 10
		}
	} //Alphabet Section
	else if (x == "G" || x == "g") {
		sScore[iCurrentThrow - 1] = "G";
		return 0; //Result 11
	}
	else if (x == "F" || x == "f") {
		sScore[iCurrentThrow - 1] = "F";
		return 0; //Result 12
	}
	else if (x == "X" || x == "x") {
		if (NofThrow() == 1) {
			sScore[iCurrentThrow - 1] = "X";
			return 0; //Result 13
		}
		else {
			return -3; //Result 14
		}
	}
	else if (x == "/") {
		if (NofThrow() == 1) {
			return -4; //Result 15
		}
		else {
			sScore[iCurrentThrow - 1] = "/";
			return 0; //Result 16
		}
	}
	else if (x == "-") {
		sScore[iCurrentThrow - 1] = "-";
		return 0; //Result 17
	}
	else if (x == "S" || x == "s") {
		if (NofThrow() == 1) {
			sScore[iCurrentThrow - 1] = "X";
			return 0; //Result 18
		}
		else {
			sScore[iCurrentThrow - 1] = "/";
			return 0; //Result 19
		}
	}
	else {
		return -1; //Result 20
	}
}

/*!
* ï∂éöóÒÇ™êÆêîílÇï\ÇµÇƒÇ¢ÇÈÇ©Çí≤Ç◊ÇÈ
* @param[inout] str ï∂éöóÒ
* @return êÆêîílÇ»ÇÁtrue
*/
inline bool IsInteger(const string& str) {
	if (str.find_first_not_of("-0123456789 \t") != string::npos) {
		return false;
	}

	return true;
}


/*
*@fn
Return the # of throw in the frame
*@param NONE
*@return the # of throw
*/
int NofThrow() {
	if (iCurrentThrow == 20) { //3rd throw
		return 3;
	}
	else if (iCurrentThrow % 2 == 0) { //2nd throw
		return 2;
	}
	else if (iCurrentThrow % 2 == 1) { //1st throw
		return 1;
	}
	else return 0; //cant go here
}
