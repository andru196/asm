#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#define msleep(msec) usleep(msec*1000)

// gcc test_ncurses.c -lncurses && ./a.out
int main()
{
    initscr();

    char str[100];
    addstr("Enter string: ");
    getstr(str);
    curs_set(0); 
    while ( true )
    {
        for ( unsigned x = getmaxx(stdscr); x; x-- ) 
        {
            clear();
            mvaddstr(getmaxy(stdscr) / 2, x, str);
            refresh();
            msleep(100);
        }
    }

    endwin();
    return 0;
}