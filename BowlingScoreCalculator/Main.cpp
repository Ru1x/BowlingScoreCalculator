/*
* Bowling Score Calculator
*
* Developed by herm1ne
*/

//-----Global Initialize-----
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;
int NewScore(string x); //prototype declaration
bool IsInteger(const string& str);
int NofThrow();
int NofFrame();
string padding(int length, int content);

//-----Declare G Variables-----
string sScore[21] = {}; //# of pins taken down (just for output)
int iPinsTakenDown[21] = {};
int iCurrentThrow = 1; //CurrentThrow (1 - 21)
string sScoreFrame[10] = {}; //Score thus far
int iThisScore[10] = {};
string sMessage = "";

void initialize() {//初期化用
	for (int i = 0; i < 21; i++) { //Initialize:(-2) Not yet
		sScore[i] = " ";
		iPinsTakenDown[i] = 0;
	}
	for (int i = 0; i < 10; i++) { //Initialize (   ) for blank output
		sScoreFrame[i] = "   ";
		iThisScore[i] = 0;
	}
	sMessage = "Let's start bowling!"; //Initial Message
	return;
}

void calculate() { //Calculate Total Score 合計得点を計算
	for (int i = 0; i < 10; i++) { 
		bool IsCalculable;
		if (sScoreFrame[i] != "   ") { //already calculated, no need to re-calculated -> skip
			continue;
		}
		if (i > NofFrame() - 1) { //The frame is not thrown yet -> skip
			continue;
		}

		if (i == 9) { //Final Frame / Special Treatment
			if (sScore[20] != " ") {
				IsCalculable = true;
				iThisScore[9] = iPinsTakenDown[18] + iPinsTakenDown[19] + iPinsTakenDown[20]; //Add up the scores of final 3 throws
			} else {
				continue;
			}
		}

		//Check if Strike or Spare or just finished
		else if (sScore[i * 2] == "X") { //Strike
			if (sScore[(i + 1) * 2] != " " && (sScore[(i + 1) * 2 + 1] != " " || sScore[(i + 2) * 2] != " ")) { //If Check calculable on strike
				iThisScore[i] = iPinsTakenDown[i * 2] + iPinsTakenDown[(i + 1) * 2]; //Basic Score and Bonus Score#1
				IsCalculable = true;

				if (sScore[(i + 1) * 2 + 1] == " ") { //Select Bonus Score #2 based on availability 次の投球が1投先か2投先か確認
					iThisScore[i] += iPinsTakenDown[(i + 2) * 2]; //Multiple Strike
				}
				else {
					iThisScore[i] += iPinsTakenDown[(i + 1) * 2 + 1]; //Strike 途中で切れた
				}
			}
			else {
				continue;
			} //Uncalculable because there is no enough score progression, wait for next throw is done
		}
		else if (sScore[i * 2 + 1] == "/") { //Spare
			if (sScore[(i + 1) * 2] != " ") { //Check if calculable on Spare
				iThisScore[i] += iPinsTakenDown[i * 2] + iPinsTakenDown[i * 2 + 1] + iPinsTakenDown[(i + 1) * 2];
				IsCalculable = true;
			}
			else {
				continue;
			} //Uncalculable because no enough score progression, wait for next throw is done
		}
		else if (i == NofFrame() - 1 && NofThrow() == 2) { //Just Finished
			if (iPinsTakenDown[i * 2] + iPinsTakenDown[i * 2 + 1] == 10) { //Spare or Strike -> Skip, wait for next throw
				continue;
			}
			else {
				IsCalculable = true;
				iThisScore[i] += iPinsTakenDown[i * 2] + iPinsTakenDown[i * 2 + 1];
			}
		}
		else {
			continue; //Uncalculable
		}

		if (IsCalculable == true) {
			int iBuffer = 0;
			for (int j = 0; j <= i; j++) {
				iBuffer += iThisScore[j];
			}
			sScoreFrame[i] = padding(3, iBuffer);
		}
	}
	return;
}

void refresh() { //Just show the current score
	system("cls"); //Console Clear

	//output
	cout << "+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------+\n";
	cout << "|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |   10   |\n";
	cout << "+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+\n";
	cout << "| " + sScore[0] + "| " + sScore[1] + "| " + sScore[2] + "| " + sScore[3] + "| " + sScore[4] + "| " + sScore[5] + "| " + sScore[6] + "| " + sScore[7] + "| " + sScore[8] + "| " + sScore[9] + "| " + sScore[10] + "| " + sScore[11] + "| " + sScore[12] + "| " + sScore[13] + "| " + sScore[14] + "| " + sScore[15] + "| " + sScore[16] + "| " + sScore[17] + "| " + sScore[18] + "| " + sScore[19] + "| " + sScore[20] + "|\n";
	cout << "+  +--+  +--+  +--+  +--+  +--+  +--+  +--+  +--+  +--+--+--+--+\n";
	cout << "|  " + sScoreFrame[0] + "|  " + sScoreFrame[1] + "|  " + sScoreFrame[2] + "|  " + sScoreFrame[3] + "|  " + sScoreFrame[4] + "|  " + sScoreFrame[5] + "|  " + sScoreFrame[6] + "|  " + sScoreFrame[7] + "|  " + sScoreFrame[8] + "|     " + sScoreFrame[9] + "|\n";
	cout << "+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------+\n";
	if (iCurrentThrow < 22) { //if iCurrentThrow == 22, it means game is over, just call refresh() for output final score ゲーム終了後はこのcoutを行わない（スコア表示のみ行う）
		cout << to_string(NofFrame()) + "フレーム目" + to_string(NofThrow()) + "投目のスコアを入力してください。" << endl;
		cout << "倒したピンの本数を入力する代わりに、以下の記号を直接入力することもできます。" << endl;
		cout << "S:スペア/ストライク　X:ストライク　/：スペア　G:ガーター　F:ファール　-:無得点" << endl;
	}
	cout << sMessage << endl;
	//For Debugging
/*	for (int i = 0; i < 21; i++) {
		cout << to_string(iPinsTakenDown[i]) + ",";
	}*/
	cout << endl;
	if (iCurrentThrow < 22) { cout << "Score>>"; }

	sMessage = ""; //Reset sMessage for future use
	return;
}


int main() //Main 
{
	string input; 
	initialize();

	for (; iCurrentThrow <= 21; iCurrentThrow++) { //This Loop is main loop, it runs until finishes

		if (iCurrentThrow == 21 && (sScore[18] != "X" && sScore[19] != "/")) { //3rd throw on the final frame is ONLY allowd when you get strike or spare in the prior frame
			iPinsTakenDown[20] = 0;
			sScore[20] = "-";
			calculate();
			iCurrentThrow++;
			break;
		}
		//ACCEPTANCE SECTION
		for (int iReturnValue;;) { //This loop is for accepting the new score and just show it
			refresh(); //Initial refresh
			if (iCurrentThrow >= 2 && sScore[iCurrentThrow - 2] == "X" && NofFrame() != 10) { //if 1st throw is a Strike, skip 2nd throw WHEN it is NOT in the final frame
				break;
			}
			input = "";
			iReturnValue = -5; //TODO implement -5 error deal
			cin >> input;
			iReturnValue = NewScore(input); //Validate
			if (iReturnValue == 0) { //PASS
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
			}
			else {
				sMessage = "Enter the score";
			}
			refresh();
		}
		//CALCULATE SECTION
		calculate();
		refresh();
	}
		sMessage = "あなたのスコアは" + sScoreFrame[9] + "点です。\n";
		if (sScoreFrame[9] == "300") { sMessage += "パーフェクトゲーム達成です。おめでとうございます。"; }
		refresh();
		cout << "Type something and press Enter key to exit...";
		cin >> input;
		getchar();
	return 0;
	
}

/*
@fn
Convert typed sScore for output and insert into corresponding sScore[X]
@param (str) # of pins taken down
@return error code 0(no error) -1(Invalid Value) -2(Value excessed max sScore(10)) -999(Unexpected)
*/
int NewScore(string x) {
	/*
	Unit Test :PASS (Aug. 01, 2015)
	*/
	if (x == "") { return -5; }
	//**********Integer Section(input is integer)**********
	if (IsInteger(x) == true) {
		if (stoi(x) == 10) {
			if (NofThrow() == 1 || NofThrow() == 3 || iCurrentThrow == 20) {
				sScore[iCurrentThrow - 1] = "X";
				iPinsTakenDown[iCurrentThrow - 1] = 10;
				return 0; //Result 1
			}
			else {
				if (sScore[iCurrentThrow - 2] == "G" || sScore[iCurrentThrow - 2] == "F" || sScore[iCurrentThrow - 2] == "-") {
					sScore[iCurrentThrow - 1] = "/";
					iPinsTakenDown[iCurrentThrow - 1] = 10;
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
				iPinsTakenDown[iCurrentThrow - 1] = stoi(x);
				return 0; //Result 5
			}
			else if (NofThrow() == 3) { //3rd throw special treatment
				if (sScore[iCurrentThrow - 3] == "X" || sScore[iCurrentThrow - 2] == "/") {
					sScore[iCurrentThrow - 1] = x;
					iPinsTakenDown[iCurrentThrow - 1] = stoi(x);
					return 0;
				}
				if (iPinsTakenDown[iCurrentThrow - 3] + iPinsTakenDown[iCurrentThrow - 2] >= 10) { //Considering 1st and 2nd are strike or one of them is strike (then you dont need to check the max)
					sScore[iCurrentThrow - 1] = x;
					iPinsTakenDown[iCurrentThrow - 1] = stoi(x);
					return 0;
				}
				else {
					if (iPinsTakenDown[iCurrentThrow - 3] + iPinsTakenDown[iCurrentThrow - 2] + stoi(x) > 10) { //Check if excess max score
						return -2; //Exceeded
					}
					else {
						sScore[iCurrentThrow - 1] = x;
						iPinsTakenDown[iCurrentThrow - 1] = stoi(x);
						return 0;
					}
				}
			}
			else {
				if (sScore[iCurrentThrow - 2] == "G" || sScore[iCurrentThrow - 2] == "F" || sScore[iCurrentThrow - 2] == "-") {
					sScore[iCurrentThrow - 1] = x;
					iPinsTakenDown[iCurrentThrow - 1] = stoi(x);
					return 0; //Result 6
				}
				else if (NofFrame() <10 && iCurrentThrow >= 2 && iPinsTakenDown[iCurrentThrow - 2] + stoi(x) > 10) {
					return -2; //Result 7 Exceed Max Score
				}
				else if (iCurrentThrow >= 2 && iPinsTakenDown[iCurrentThrow - 2] + stoi(x) == 10) {
					sScore[iCurrentThrow - 1] = "/";
					iPinsTakenDown[iCurrentThrow - 1] = stoi(x);
					return 0; //Result 8
				}
				else {
					sScore[iCurrentThrow - 1] = x;
					iPinsTakenDown[iCurrentThrow - 1] = stoi(x);
					return 0; //Result 9
				}
			}
		}
		else { //Too Big or Too Small Number Entered!
			return -1; //Result 10
		}
		//**********End of Integer Section**********

	} //**********Alphabet Section**********
	else if (x == "G" || x == "g") { //Gutter
		sScore[iCurrentThrow - 1] = "G";
		iPinsTakenDown[iCurrentThrow - 1] = 0;
		return 0; //Result 11
	}
	else if (x == "F" || x == "f") { //Foul
		sScore[iCurrentThrow - 1] = "F";
		iPinsTakenDown[iCurrentThrow - 1] = 0;
		return 0; //Result 12
	}
	else if (x == "X" || x == "x") { //Strike
		if (NofThrow() == 1 || NofThrow() == 3 || (NofThrow() == 2 && NofFrame() == 10)) { //Validate so that Strike only can be in the 1st throw && <Strike can be in the second throw of the FINAL Frame>
			sScore[iCurrentThrow - 1] = "X";
			iPinsTakenDown[iCurrentThrow - 1] = 10;
			return 0; //Result 13
		}
		else {
			return -3; //Result 14 STRIKE CANNOT BE IN 2ND THROW!
		}
	}
	else if (x == "/") { //Spare
		if (NofThrow() == 1 || NofThrow() == 3) { //Validate so that Spare only cannot be in the 1st throw
			return -4; //Result 15 SPARE CANNOT BE IN 1ST THROW!
		}
		else {
			sScore[iCurrentThrow - 1] = "/";
			iPinsTakenDown[iCurrentThrow - 1] = 10 - iPinsTakenDown[iCurrentThrow - 2];
			return 0; //Result 16
		}
	}
	else if (x == "-") { 
		sScore[iCurrentThrow - 1] = "-";
		iPinsTakenDown[iCurrentThrow - 1] = 0;
		return 0; //Result 17
	}
	else if (x == "S" || x == "s") { //Strike or Spare. Need to determine by the following statements
		if (NofThrow() == 1) {
			sScore[iCurrentThrow - 1] = "X"; //oh it's strike, maybe
			iPinsTakenDown[iCurrentThrow - 1] = 10;
			return 0; //Result 18
		}
		else {
			sScore[iCurrentThrow - 1] = "/"; //oh it's spare, maybe
			iPinsTakenDown[iCurrentThrow - 1] = 10 - iPinsTakenDown[iCurrentThrow - 2];
			return 0; //Result 19
		}
	}
	else {
		return -1; //Result 20 //Other unacceptable value inputted!
	}
}

/*!
* 文字列が整数値を表しているかを調べる
* @param[inout] str 文字列
* @return 整数値ならtrue
*/
inline bool IsInteger(const string& str) {
	if (str.find_first_not_of("0123456789 \t") != string::npos) {
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
	/*
	Unit Test :PASS (Aug. 01, 2015)
	*/
	if (iCurrentThrow == 21) { //3rd throw
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

/*
*@fn
Return the # of Frame
*@param NONE
*@return the # of Frame
*/
int NofFrame() {
	/*
	Unit Test :PASS (Aug. 01, 2015)
	*/
	int iFrame;
	iFrame = floor((iCurrentThrow + 1) / 2);
	if (iCurrentThrow == 21) {
		return 10;
	}
	return iFrame;
}

string padding(int length, int content) {

	string sContent = to_string(content);
	stringstream output;
	for (int i = 0; i < length - sContent.length(); i++) {
		output << " ";
	}

	output << sContent;

	return output.str();
}
