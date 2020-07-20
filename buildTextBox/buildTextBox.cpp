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
	int i_pos;
	int currLen = 0;

	if(maxLen <= 0)
	{
		werase(textWin);
		wrefresh(textWin);
		printw("ERROR: Invalid max length of %d passed into buildTextBox()\n", maxLen);
		refresh();
		return NULL;
	}
	if(textWin == NULL)
	{
		werase(textWin);
		wrefresh(textWin);
		printw("ERROR: NULL window passed into buildTextBox()\n");
		refresh();
		return NULL;
	}

	keypad(textWin, true);
	cbreak();	
	noecho();

	getmaxyx(textWin, y_max, x_max);

	wmove(textWin, y_pos, x_pos);

	input = (char*)malloc(sizeof(char)*maxLen);
	i_pos = 0;

	for(int i = 0; i < maxLen; i++)
	{
		input[i] = ' ';
	}

	in = ' ';
	while((int)in != 10 && (int)in != 9) // while not enter or tab
	{
		in = wgetch(textWin);
		if((int)in == 7) // Backspace
		{
			if(x_pos > 1) 
			{
				x_pos--;
				wmove(textWin, y_pos, x_pos);
				wprintw(textWin, "%c", ' ');
				currLen--;
			}
			else if(y_pos > 1)
			{
				x_pos = x_max - 2;
				y_pos--;
				wmove(textWin, y_pos, x_pos);
				wprintw(textWin, "%c", ' ');
				currLen--;
			}
		}
		else if((int)in == 2) // Down Arrow
		{
			if(y_pos < y_max - 2) 
			{
				y_pos++;
			}
		}
		else if((int)in == 3) // Up Arrow
		{
			if(y_pos > 1) 
			{
				y_pos--;
			}
		}
		else if((int)in == 4) // Back Arrow
		{
			if(x_pos > 1)
			{
				x_pos--;
			}
			else if(y_pos > 1)
			{
				x_pos = x_max - 2;
				y_pos--;
			}
		}
		else if((int)in == 5) // Forward Arrow
		{
			if(x_pos < x_max - 2)
			{
				x_pos++;
			}
			else if(y_pos < y_max - 2)
			{
				y_pos++;
				x_pos = 1;
			}
		}
		else 	// Input character
		{
			if(currLen < maxLen)
			{
				if(x_pos < x_max - 2) 
				{
					input[i_pos] = in;
					wprintw(textWin, "%c", in);
					currLen++;					
					i_pos++;
					x_pos++;
				}
				else if(y_pos < y_max - 2) 
				{
					input[i_pos] = in;
					wprintw(textWin, "%c", in);
					currLen++;
					i_pos++;
					x_pos = 1;
					y_pos++;
				}
			}
		}
	
		if(y_pos >= y_max - 1 || x_pos >= x_max - 1) 
		{
			wclear(textWin);
			wrefresh(textWin);
			printw("ERROR: Out of bounds\n");
			refresh();
			return NULL;
		}
	
		wmove(textWin, y_pos, x_pos);
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
	box(textBox, '|', '-');
	
	wrefresh(textBox);
	refresh();

	input = buildTextBox(textBox, maxLen);
	werase(textBox);
	
	wrefresh(textBox);
	refresh();
	
	delwin(textBox);
	
	printw("Press any key to exit...");
	refresh();
	
	getchar();
	endwin();

	printf("Input:\n");
	if(input != NULL)
	{
		for(int i = 0; i < maxLen; i++) 
		{
			printf("%c", input[i]);
		}
		printf("\n");
	}
	else
	{
		printf("NULL\n");
	}
	
	// Clean up
	if(input != NULL) {
		free(input);
		input = NULL;
	}

}

