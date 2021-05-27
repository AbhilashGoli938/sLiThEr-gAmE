#include "ui.h"
#include <ncurses.h>
extern WINDOW *stdscr;

//save whatever you have on screen
// it will clear the screen



void init_ui()
{
    setlocale(LC_ALL, ""); //overrides default locale
    initscr(); // initialize ncurses mode
    nodelay(stdscr, TRUE); // make getch non blocking call
    //by default in terminal keys will be printed
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); // enable reading of functional arrow other keys
}



void tear_down_ui()
{
     endwin(); // exit the ncurses mode
}

void paint_border()
{
     if(has_colors() == FALSE)
	{	endwin();
        move(0,15);
		printw("Your terminal does not support color\n");
		exit(1); 
	}
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_RED,COLOR_BLACK);


    // ncurses provides COLS
    for(int i=0; i< COLS; i++)
    {
        move(0,i); // moving to colomn i in top row
        attron(COLOR_PAIR(1));
        addstr("\u2588");
        //stdscr.addstr( "Pretty text", curses.COLOR_PAIR(1) )
        attroff(COLOR_PAIR(1));
        move(LINES-1, i);
        attron(COLOR_PAIR(1));
        addstr("\u2588");
        attroff(COLOR_PAIR(1));
        //getch();
        
    }

    for(int i=0; i< LINES; i++)
    {
        move(i,0); //move to first col of line
        attron(COLOR_PAIR(2));
        addstr("\u2588");
        attroff(COLOR_PAIR(2));
        move(i, COLS - 1);// move to last col of line
        attron(COLOR_PAIR(2));
        addstr("\u2588");
        attroff(COLOR_PAIR(2));
        //getch();
    }
    
    

}
