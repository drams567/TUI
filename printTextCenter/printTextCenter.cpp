#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

using namespace std;

int printTextCenter(WINDOW* win, const char* text, int len) 
{
	int y_max, x_max;
	int y_pos, x_pos;
	int i_pos;
	bool endOfWin;

	getmaxyx(win, y_max, x_max);
	if(y_start >= (y_max - 1) || x_start >= (x_max - 1) || y_start <= 0 || x_start <= 0)
	{
		mvprintw(0, 0, "printTextWrap: ERROR invalid start position of (%d,%d)(y, x).\n", y_start, x_start);
		refresh();
		return 1;
	}

	y_pos = y_start;
	x_pos = x_start;
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
				if((i_pos + 1) < len && text[i_pos+1] == ' ')
				{
					i_pos++; // skip space at new line
				}
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

	return (len - i_pos); // number of characters not printed
}

int main() {
	string outMsg = "David is my test message to output.";
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

	ret = printTextWrap(textBox, 6, 5, outMsg.c_str(), (int)outMsg.size());
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

