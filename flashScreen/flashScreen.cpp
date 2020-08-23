#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

using namespace std;


int main() {

	cbreak();
	noecho();

	// Initialize ncurses
	initscr();
	refresh();

	int width = 10;
	int height = 10;

	// Create window for text box
	WINDOW * textBox = newwin(width, height, 0, 0);
	box(textBox, '|', '-');
	
	wrefresh(textBox);
	refresh();

	ret = printTextWrap(textBox, outMsg.c_str(), (int)outMsg.size());
	werase(textBox);
	
	wrefresh(textBox);
	refresh();
	
	delwin(textBox);
	
	printw("ret = %d", ret);
	refresh();
	getchar();

	printw("Press any key to exit...");
	refresh();
	getchar();

	endwin();
	
}

