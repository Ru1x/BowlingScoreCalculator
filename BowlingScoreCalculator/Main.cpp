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
bool IsInteger(const string &str);
int NofThrow();

//-----Declare G Variables-----
string score[21] = {}; //# of pins taken down (-1:N/A because of Spare or Strike -2:NotYet 0:Score is zero)
int CurrentThrow = 1; //CurrentFrame (1 - 21)
string ScoreFrame[10] = {}; //Score thus far
//string Message = "";

void initialize() {
	for (int i = 0; i < 21; i++) { //Initialize:(-2) Not yet
		score[i] = " ";
	}
	for (int i = 0; i < 10; i++) { //Initialize (   ) for blank output
		ScoreFrame[i] = "   ";
	}
	//Message = "Let's start bowling!";
	return;
}

void calculate() {

}

void refresh() {
	system("cls"); //Console Clear

	//output
	cout << "+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------+\n";
	cout << "|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |   10   |\n";
	cout << "+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+\n";
	cout << "| " + score[0] + "| " + score[1] + "| " + score[2] + "| " + score[3] + "| " + score[4] + "| " + score[5] + "| " + score[6] + "| " + score[7] + "| " + score[8] + "| " + score[9] + "| " + score[10] + "| " + score[11] + "| " + score[12] + "| " + score[13] + "| " + score[14] + "| " + score[15] + "| " + score[16] + "| " + score[17] + "| " + score[18] + "| " + score[19] + "| " + score[20] + "|\n";
	cout << "+  +--+  +--+  +--+  +--+  +--+  +--+  +--+  +--+  +--+--+--+--+\n";
	cout << "|  " + ScoreFrame[0] + "|  " + ScoreFrame[1] + "|  " + ScoreFrame[2] + "|  " + ScoreFrame[3] + "|  " + ScoreFrame[4] + "|  " + ScoreFrame[5] + "|  " + ScoreFrame[6] + "|  " + ScoreFrame[7] + "|  " + ScoreFrame[8] + "|     " + ScoreFrame[9] + "|\n";
	cout << "+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------+\n";
	return;
}



int main() //Main
{
	string xa;
	initialize();
	for (int i = 0; i <= 10; i++) {
		cin >> xa;
		NewScore(xa);
	}

	return 0;
}
/*
@fn
Convert typed score for output and insert into corresponding score[X]
@param (str) # of pins taken down
@return error code 0(no error) -1(Invalid Value) -2(Value excessed max score(10)) -999(Unexpected)
*/
int NewScore(string x) {
	//This chart is so complicated you can find table chart at :
	//TODO Upload table chart
	if (IsInteger(x) == true) { //IntegerSection
		if (stoi(x) == 10) {
			if (NofThrow() ==1) {
				score[CurrentThrow - 1] = "X";
				return 0; //Result 1
			} else {
				if(score[CurrentThrow -2] == "G" || score[CurrentThrow - 2] == "F" || score[CurrentThrow - 2] == "-") {
					score[CurrentThrow - 1] = "/";
					return 0; //Result 2
				} else {
					return -2; //Result 3
				}
			}
		}
		else if (stoi(x) == 0) {
			score[CurrentThrow - 1] = "-";
			return 0; //Result 4
		}
		else if (1<=stoi(x) && stoi(x)<=9) {
			if (NofThrow() == 1){
			score[CurrentThrow - 1] = x;
			return 0; //Result 5
			} else {
				if (score[CurrentThrow - 2] == "G" || score[CurrentThrow - 2] == "F" || score[CurrentThrow - 2] == "-") {
					score[CurrentThrow - 1] = x;
					return 0; //Result 6
				}
				else if(stoi(score[CurrentThrow -2]) + stoi(x) > 10) {
					return -2; //Result 7 Exceed Max Score
				}
				else if (stoi(score[CurrentThrow - 2]) + stoi(x) == 10) {
					score[CurrentThrow - 1] = "/";
					return 0; //Result 8
				}
				else {
					score[CurrentThrow - 1] = x;
					return 0; //Result 9
				}
			}
		}
		else { //Too Big or Too Small Number Entered!
			return -1; //Result 10
		}
	} //Alphabet Section
	else if (x == "G") {
		score[CurrentThrow - 1] = "G";
		return 0; //Result 11
	}
	else if (x == "F") {
		score[CurrentThrow - 1] = "F";
		return 0; //Result 12
	}
	else if (x == "X") {
		if (NofThrow() == 1) {
			score[CurrentThrow - 1] = "X";
			return 0; //Result 13
		} else {
			return -3; //Result 14
		}
	}
	else if (x == "/") {
		if (NofThrow() == 1) {
			return -4; //Result 15
		} else {
			score[CurrentThrow - 1] = "/";
			return 0; //Result 16
		}
	}
	else if (x == "-") {
		score[CurrentThrow - 1] = "-";
		return 0; //Result 17
	}
	else if (x == "S") {
		if (NofThrow() == 1) {
			score[CurrentThrow - 1] = "X";
			return 0; //Result 18
		}
		else {
			score[CurrentThrow - 1] = "/";
			return 0; //Result 19
		}
	}
	else {
		return -1; //Result 20
	}
}

/*!
* •¶š—ñ‚ª®”’l‚ğ•\‚µ‚Ä‚¢‚é‚©‚ğ’²‚×‚é
* @param[inout] str •¶š—ñ
* @return ®”’l‚È‚çtrue
*/
inline bool IsInteger(const string &str)
{
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
	if (CurrentThrow == 20) {return 3;}
	else if (CurrentThrow % 2 == 0) { return 1; }
	else if (CurrentThrow % 2 == 1) { return 2; }
	else return 0; //cant go here
}