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

	// Check Params //
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

	// Adjust settings for input
	keypad(textWin, true);
	cbreak();	
	noecho();

	// Get screen size
	getmaxyx(textWin, y_max, x_max);

	// Initialize input buffer
	input = (char*)malloc(sizeof(char)*maxLen);
	for(int i = 0; i < maxLen; i++)
	{
		input[i] = ' ';
	}
	input[maxLen - 1] = '\0';
	
	// Initialize for input
	i_pos = 0;
	in = ' ';
	wmove(textWin, y_pos, x_pos);
	
	// Get Input //
	while((int)in != 10 && (int)in != 9) // while not enter or tab
	{
		// Get Character and Handle //
		in = wgetch(textWin);
		// Backspace, replace previous character with space
		if((int)in == 7)
		{
			// previous character is on same line
			if(x_pos > 1)
			{
				x_pos--;
				wmove(textWin, y_pos, x_pos);
				wprintw(textWin, "%c", ' ');
				
				i_pos--;
				input[i_pos] = ' ';
				currLen--;
			}
			// previous character is on line above
			else if(y_pos > 1)
			{
				x_pos = x_max - 2;
				y_pos--;
				wmove(textWin, y_pos, x_pos);
				wprintw(textWin, "%c", ' ');
				
				i_pos--;
				input[i_pos] = ' ';
				currLen--;
			}
		}
		// Down Arrow, move cursor down
		else if((int)in == 2) // Down Arrow
		{
			if(y_pos < y_max - 2) 
			{
				y_pos++;
				i_pos += x_max - 1;
			}
		}
		// Up Arrow, move cursor up
		else if((int)in == 3) // Up Arrow
		{
			if(y_pos > 1) 
			{
				y_pos--;
				i_pos -= x_max - 1;
			}
		}
		// Back Arrow, move cursor to previous character
		else if((int)in == 4) // Back Arrow
		{
			if(x_pos > 1)
			{
				x_pos--;
				i_pos--;
			}
			else if(y_pos > 1)
			{
				x_pos = x_max - 2;
				y_pos--;
				i_pos--;
			}
		}
		// Forward Arrow, move cursor to next character
		else if((int)in == 5) // Forward Arrow
		{
			if(x_pos < x_max - 2)
			{
				x_pos++;
				i_pos++;
			}
			else if(y_pos < y_max - 2)
			{
				y_pos++;
				x_pos = 1;
				i_pos++;
			}
		}
		// Text Character, add character to current position
		else if((int)in != 10 && (int)in != 9)
		{
			if(currLen < maxLen - 1) // save room for null terminator
			{
				if(x_pos < x_max - 2) 
				{
					wprintw(textWin, "%c", in);
					x_pos++;
					
					input[i_pos] = in;
					currLen++;					
					i_pos++;
				}
				else if(y_pos < y_max - 2) 
				{
					wprintw(textWin, "%c", in);
					x_pos = 1;
					y_pos++;
					
					input[i_pos] = in;
					currLen++;
					i_pos++;
				}
			}
		}
	
		// bound check cursor postion, for debugging purposes
		if(y_pos >= y_max - 1 || x_pos >= x_max - 1) 
		{
			wclear(textWin);
			wrefresh(textWin);
			printw("ERROR: Out of bounds\n");
			refresh();
			return NULL;
		}

		// Update cursor and screen	
		wmove(textWin, y_pos, x_pos);
		wrefresh(textWin);
	}
		
	return input;
}

int main() {
	char* input = NULL;
	int maxLen = 500;

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

