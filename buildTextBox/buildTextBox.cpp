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
	cbreak();	
	noecho();

	getmaxyx(textWin, y_max, x_max);

	wmove(textWin, y_pos, x_pos);

	input = (char*)malloc(sizeof(char)*maxLen);

	in = ' ';
	while((int)in != 10 && (int)in != 9) 
	{
		in = wgetch(textWin);
		if((int)in == 7) // Backspace
		{
			if(x_pos > 1) 
			{
				x_pos--;
				wmove(textWin, y_pos, x_pos);
				wdelch(textWin);
				currLen--;
			}
			else
			{
				x_pos = x_max - 1;
				y_pos--;
				wmove(textWin, y_pos, x_pos);
				wdelch(textWin);
				currLen--;
			}
		}
		else if((int)in == 2)
		{
			
		}
		else if((int)in == 3)
		{
		
		}
		else if((int)in == 4)
		{
		
		}
		else if((int)in == 5)
		{
		
		}
		else 	// Input character
		{
			currLen++;
			wprintw(textWin, "%c", in);
			if(x_pos < x_max - 1) 
			{
				x_pos++;
			}
			else 
			{
				x_pos = 1;
				y_pos++;
			}
			wmove(textWin, y_pos, x_pos);
		}
		
		wrefresh(textWin);
	}
		
	return input;
}

int main() {
	char* input = NULL;
	int maxLen = 123;

	cbreak();
	noecho();

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

