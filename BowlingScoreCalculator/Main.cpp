/*
* Bowling Score Calculator
*
* Developed by herm1ne
*/

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int pin[21] = {}; //# of pins taken down (-1:N/A because of Spare or Strike -2:NotYet 0:Score is zero)

int CurrentFrame = 1; //CurrentFrame (0:NotStarted - 10)
string ScoreFrame[10] = {};

//string Message = "";

void initialize() {
	for (int i = 0; i < 21; i++) {
		pin[i] = -2;
	}
	for (int i = 0; i < 10; i++) {
		ScoreFrame[i] = "   ";
	}
	//Message = "Let's start bowling!";
	return;
}

void refresh() {
	system("cls"); //Console Clear

	//Recieve Data and replace
	string score[21] = {};

	for (int i = 0; i < 21; i++) {
		if (pin[i] == -1 || pin[i] == -2) {
			score[i] = "  ";
		}
		else if (pin[i] == 0) {
			score[i] = "--";
		}
		else {
			score[i] = pin[i];
		}
	}

	//Find ScoreFrame
	//<<Calculate HERE>//

	//ScoreFrame Replace for output



	//output
	cout << "+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------+\n";
	cout << "|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |   10   |\n";
	cout << "+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------+\n";
	cout << "|" + score[0] + "|" + score[1] + "|" + score[2] + "|" + score[3] + "|" + score[4] + "|" + score[5] + "|" + score[6] + "|" + score[7] + "|" + score[8] + "|" + score[9] + "|" + score[10] + "|" + score[11] + "|" + score[12] + "|" + score[13] + "|" + score[14] + "|" + score[15] + "|" + score[16] + "|" + score[17] + "|" + score[18] + "|" + score[19] + "|" + score[20] + "|\n";
	cout << "+  +--+  +--+  +--+  +--+  +--+  +--+  +--+  +--+  +--+--+--+--+\n";
	cout << "|  " + ScoreFrame[0] + "|  " + ScoreFrame[1] + "|  " + ScoreFrame[2] + "|  " + ScoreFrame[3] + "|  " + ScoreFrame[4] + "|  " + ScoreFrame[5] + "|  " + ScoreFrame[6] + "|  " + ScoreFrame[7] + "|  " + ScoreFrame[8] + "|     " + ScoreFrame[9] + "|\n";
	cout << "+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------+\n";
	return;
}

int main() //Main
{
	initialize();
	refresh();
}
