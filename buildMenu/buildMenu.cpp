#include <iostream>
#include <string>
#include <curses.h>

using namespace std;

int buildMenu(WINDOW* menuWin, std::string items[], int size) {
	int choice = -1;	
	int curr = 0;	
	char in = ' ';

	keypad(menuWin, true);

	while(in != 10) {
		for(int i = 0; i < size; i++) {
			if(i == curr) {
				wattron(menuWin, A_STANDOUT);
				mvwprintw(menuWin, i + 1, 1, items[i].c_str());
				wattroff(menuWin, A_STANDOUT);
			}
			else {
				mvwprintw(menuWin, i + 1, 1, items[i].c_str());
			}
		}
		wrefresh(menuWin);
		in = wgetch(menuWin);
		
		switch(in) {
			case 3: // up arrow
				if(curr > 0) {
					curr--;
				}
				break;
			case 2: // down arrow
				if(curr < size - 1) {
					curr++;
				}
				break;
			
			default: // out of bounds
				curr = curr;
				break;
		}
			
	}

	choice = curr + 1;	
	return choice;
}

int main() {

	initscr();

	refresh();

	int y_max, x_max;
	getmaxyx(stdscr, y_max, x_max);

	int width = 40;
	int height = 70;

	WINDOW * mainMenu = newwin(width, height, 0, 0);
	
	wrefresh(mainMenu);
	refresh();

	string items[] = {"option 1"};
	int size = 1;	

	int choice = buildMenu(mainMenu, items, size);
	delwin(mainMenu);
	
	refresh();
	
	printw("Press any key to exit...");
	refresh();
	
	getchar();
	endwin();


	cout << "\n" << choice << "\n";
	return 0;
}

