#ifndef TUI_H
#define TUI_H

#include <string>
#include <ncurses.h>

using namespace std;

int printTextWrap(WINDOW* win, int y_start, int x_start, const char* text, int len)
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

char* buildTextBox(WINDOW* textWin, int maxLen) {
    char* input = NULL;
    char in;    
    int y_max, x_max;
    int y_pos = 1, x_pos = 1;
    int i_pos;
    int currLen = 0;

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

        // Update cursor and screen 
        wmove(textWin, y_pos, x_pos);
        wrefresh(textWin);
    }

    return input;
}


#endif
