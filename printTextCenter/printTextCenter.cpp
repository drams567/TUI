#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <cstring>
#include <cmath>

using namespace std;

void tokenizeString(vector<string> &tokens, char* source, const char* delim) {
	// Tokenize string
    char* curr = strtok(source, delim);
    while(curr != NULL) {
        tokens.push_back(string(curr));
        curr = strtok(NULL, delim);
    }
}

int printTextWrapCenter(WINDOW* win, const char* text, const int len) {
	// Copy source text
	char newText[len+1];
	for(int i = 0; i < len; i++)
		newText[i] = text[i];
	newText[len] = '\0';

	// Tokenize print text
	vector<string> tokenList;
	tokenizeString(tokenList, newText, " \n");
	int numTokens = (int)tokenList.size();

	// Calc number of chracters to be printed
	int numChars = 0;
	for(int i = 0; i < numTokens; i++) {
		numChars += (int)tokenList.at(i).length() + 1; // add 1 to account for spaces
	}
	numChars--; // discount last space

	// Calc total space
	int max_y, max_x;
	getmaxyx(win, max_y, max_x);
	max_y--; // discount end border
	max_x--; //

	// Create lines
	string line = tokenList[0];
	vector<string> lineList;
	for(int i = 1; i < numTokens; i++) {
		string token = tokenList[i];
		if((int)(line.length() + 1 + token.length()) < max_x) {
			line += " " + token;
		}
		else {
			lineList.push_back(line);
			line = token;
		}
	}
	if(lineList.size() == 0 || lineList[lineList.size()-1] != line) {
		lineList.push_back(line);
	}

	// Check for too many lines
	int numLines;
	int missingChars = 0;
	if((int)lineList.size() > max_y) {
		numLines = max_y;
		for(int i = max_y; i < (int)lineList.size(); i++) {
			line = lineList[i];
			missingChars += (int)line.length();
			if(line[line.length()-1] != ' ' && i < (int)lineList.size()-1) {
				missingChars++; // account for spaces
			}
		}
	}
	else {
		numLines = (int)lineList.size();
		missingChars = 0;
	}
	
	// Print lines
	int pos_y, pos_x;
	pos_y = floor((double)(max_y - numLines) / 2.0) + 1;
	for(int i = 0; i < numLines; i++) {
		line = lineList.at(i);
		pos_x = floor((max_x - (int)line.length()) / 2.0) + 1;
		mvwprintw(win, pos_y, pos_x, "%s", line.c_str());
		pos_y++;
	}

	return missingChars;
}

int main(int argc, char* argv[]) {
	string outMsg = "David yeah what the fuck is up homie dog from the south my homie ass momma";
	int ret;

	cbreak();
	noecho();

	// Initialize ncurses
	initscr();
	refresh();

	int height = atoi(argv[1]);
	int width = atoi(argv[2]);

	// Create window for text box
	WINDOW * textBox = newwin(width, height, 0, 0);
	box(textBox, '|', '-');
	
	wrefresh(textBox);
	refresh();

	ret = printTextWrapCenter(textBox, outMsg.c_str(), (int)outMsg.size());
	wrefresh(textBox);
	refresh();
	getchar();
	
	werase(textBox);
	wrefresh(textBox);
	refresh();
	
	delwin(textBox);
	
	printw("ret = %d", ret);
	refresh();
	getchar();

	endwin();
	
}

