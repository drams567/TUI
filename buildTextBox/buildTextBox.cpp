#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

using namespace std;

char* buildTextBox(WINDOW* textWin, int maxLen) {
	char* input = NULL;
	char in;	
	int y_max, x_max;
	int y_pos = 1, x_pos = 1;
	int currLen = 0;

	keypad(textWin, true);
	
	getmaxyx(textWin, y_max, x_max);

	wmove(textWin, y_pos, x_pos);

	input = (char*)malloc(sizeof(char)*maxLen);

	in = ' ';
	while((int)in != 10) {
		in = wgetch(textWin);
		if(x_pos < x_max) {
			x_pos++;
		}
		else {
			x_pos = 1;
			y_pos++;
		}
		mvwprintw(textWin, y_pos, x_pos, "%c", in);
		wrefresh(textWin);
	}
		
	return input;
}

int main() {
	char* input = NULL;
	int maxLen = 123;

	// Initialize ncurses
	initscr();
	refresh();

	int width = 10;
	int height = 10;

	// Create window for text box
	WINDOW * textBox = newwin(width, height, 0, 0);
	
	wrefresh(textBox);
	refresh();

	input = buildTextBox(textBox, maxLen);
	delwin(textBox);
	
	refresh();
	
	printw("Press any key to exit...");
	refresh();
	
	getchar();
	endwin();
	
	// Clean up
	if(input != NULL) {
		free(input);
		input = NULL;
	}

}

