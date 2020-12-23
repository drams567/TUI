#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <cstring>

using namespace std;

void tokenizeString(vector<string> &tokens, char* source, const char* delim) {
	// Tokenize string
    char* curr = strtok(source, delim);
    while(curr != NULL) {
        tokens.push_back(string(curr));
        curr = strtok(NULL, delim);
    }
}

int printTextWrap(WINDOW* win, int y_start, int x_start, const char* text, int len) {
	// Copy print text
	char newText[len+1];
	for(int i = 0; i < len; i++)
		newText[i] = text[i];
	newText[len] = '\0';

	// Tokenize print text
	vector<string> tokenList;
	tokenizeString(tokenList, newText, " \n");
	
	int y_pos = y_start, x_pos = x_start;
	int y_max, x_max;
	getmaxyx(win, y_max, x_max);
	y_max--;
	x_max--;
	int i = 0;
	int numTokens = (int)tokenList.size();
	
	while(i < numTokens && y_pos < y_max) {
		string token = tokenList.at(i);
		int len = (int)token.size();
		if(len <= (x_max - x_pos)) {
			mvwprintw(win, y_pos, x_pos, "%s", token.c_str());
			x_pos += len;
			
			if(x_pos < x_max) {
				mvwprintw(win, y_pos, x_pos, "%c", ' ');
				x_pos++;
			}
			i++;
		}
		else {
			y_pos++;
			x_pos = 1;
		}
	}
	
	// Check for missed tokens
	int missedChars = 0;
	while(i < numTokens) {
		missedChars += (int)tokenList.at(i).size();
		i++;
	}

	return missedChars;
}

int main(int argc, char* argv[]) {
	string outMsg = "David";
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

	ret = printTextWrap(textBox, 1, 1, outMsg.c_str(), (int)outMsg.size());
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

