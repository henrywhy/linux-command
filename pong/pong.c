#include <stdio.h>
#include <curses.h>

int main(int argc, char * argv[])
{
	initscr();
	clear();
	addstr("Hello World");	
	move(LINES-1, 0);
	refresh();
	getch();
	endwin();
	return 0;
}
