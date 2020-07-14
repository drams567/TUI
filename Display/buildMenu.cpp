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

	wclear(menuWin);
	wrefresh(menuWin);

	choice = curr + 1;	
	return choice;
}

int main() {

	initscr();

	refresh();

	int y_max, x_max;
	getmaxyx(stdscr, y_max, x_max);
	
	// Stats Window
	int stats_height = 10;
	int stats_width = 20;
	int stats_y = 0;
	int stats_x = 0;
	WINDOW * statsWin = newwin(stats_height, stats_width, stats_y, stats_x);
	box(statsWin, '|', '-');
	mvwprintw(statsWin, 1, 1, "Stats Window");
	wrefresh(statsWin);	
	
	// Inventory Menu
	int inv_height = y_max - stats_height;
	int inv_width = stats_width;
	int inv_y = y_max - inv_height;
	int inv_x = 0;
	WINDOW * invWin = newwin(inv_height, inv_width, inv_y, inv_x);	
	box(invWin, '|', '-');
	mvwprintw(invWin, 1, 1, "Inventory");
	wrefresh(invWin);	

	// Menu Window
	int menu_height = 10;
	int menu_width = x_max - (stats_width + 1);
	int menu_y = y_max - menu_height;
	int menu_x = x_max - menu_width;
	WINDOW * menuWin = newwin(menu_height, menu_width, menu_y, menu_x);
	box(menuWin, '|', '-');
	wrefresh(menuWin);	
	
	// Prompt window
	int prompt_height = 5;
	int prompt_width = menu_width;
	int prompt_y = y_max - (menu_height + prompt_height);
	int prompt_x = x_max - prompt_width;
	WINDOW * promptWin = newwin(prompt_height, prompt_width, prompt_y, prompt_x);
	box(promptWin, '|', '-');
	mvwprintw(promptWin, 1, 1, "prompt");
	wrefresh(promptWin);	

	// Display window
	int dis_height = y_max - (prompt_height + menu_height);
	int dis_width = x_max - (stats_width + 1);
	int dis_y = 0;
	int dis_x = stats_width + 1;
	WINDOW * displayWin = newwin(dis_height, dis_width, dis_y, dis_x);	
	box(displayWin, '|', '-');
	mvwprintw(displayWin, 1, 1, "display window");
	wrefresh(displayWin);	


	// Build Main Menu
	string items[] = {"option 1", "option 2", "option 3", "option 4"};
	int size = 4;	

	int choice = buildMenu(menuWin, items, size);


	wclear(menuWin);
	wclear(statsWin);
	wclear(invWin);
	wclear(promptWin);
	wclear(displayWin);

	wrefresh(menuWin);
	wrefresh(statsWin);
	wrefresh(invWin);
	wrefresh(promptWin);
	wrefresh(displayWin);

	delwin(menuWin);
	delwin(statsWin);	
	delwin(invWin);
	delwin(promptWin);
	delwin(displayWin);

	refresh();
	
	printw("Press any key to exit...");
	refresh();
	
	getchar();
	endwin();


	cout << "\n" << choice << "\n";
	return 0;
}

