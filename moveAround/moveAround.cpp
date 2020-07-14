#include <iostream>
#include <string>
#include <ncurses.h>

using namespace std;

void moveTextAroundWindow(WINDOW* win, string text) {
	int height = 0;
	int width = 0;

	getmaxyx(win, height, width);

	int w = 1;
	int h = 1;

	char in;
	while(in != 'p') {
		switch(in) {
			case 'w':
				if(h > 1) {
					h--;
				}
				break;
			case 's':
				if(h < height - 2) {
					h++;
				}
				break;
			case 'a':
				if(w > 1) {
					w--;
				}
				break;
			case 'd':
				if( w < width - (1 + (int)text.length()) ) {
					w++;
				}
				break;
			default:
				break;			

		}

		wclear(win);
		box(win, 0, 0);
		mvwprintw(win, h, w, text.c_str());		
		wrefresh(win);

		in = getchar();
	}	

	wclear(win);
}

int main() {

	initscr();
	cbreak();
	raw();

	int width = 70;
	int height = 40;

	WINDOW * win = newwin(height, width, 0, 0);
	refresh();
	

	string text = "666";

	moveTextAroundWindow(win, text);

	delwin(win);
	
	clear();
	refresh();
	mvprintw(10, 10, "Press any key to exit...");
	refresh();
	
	getchar();

	endwin();
	
	return 0;
}
