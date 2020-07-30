#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

using namespace std;

int printTextWrap(WINDOW* win, const char* text, int len) 
{
	int y_max, x_max;
	int y_pos, x_pos;
	int i_pos;
	int maxLen;
	bool endOfWin;

	getmaxyx(win, y_max, x_max);
	
	maxLen = ((x_max - 2)*(y_max - 2));

	if(len > maxLen) 
	{
		wprintw(win, "ERROR: text exceeds maximum length for window. Max length is %d, length of test is %d", maxLen, len);
		return -1;
	}


	y_pos = 1;
	x_pos = 1;
	wmove(win, y_pos, x_pos);

	i_pos = 0;
	while(i_pos < len && endOfWin == false)
	{
		wprintw(win, "%c", text[i_pos]);
		if(x_pos < x_max - 2)
		{
			x_pos++;
		}
		else
		{
			x_pos = 1;
			if(y_pos < y_max - 2)
			{
				y_pos++;
			}
			else
			{
				endOfWin = true;
			}
		}
		wmove(win, y_pos, x_pos);
		i_pos++;
	}
	wrefresh(win);
	getchar();

	return (maxLen - i_pos); // i_pos will already be adjusted to number of char printed
}

int main() {
	string outMsg = "This is my test message to output.";
	int ret;

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

