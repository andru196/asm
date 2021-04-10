#include <ncurses.h>
//#define msleep(msec) usleep(msec*1000)

// gcc test_ncurses.c -lncurses && ./a.out
/*int main()
{
    WINDOW	*arena_window;
	WINDOW	*info_window;
    initscr();
	timeout(1);
	arena_window = newwin(70, 200, 3, 10);
	//box(arena_window, 0, 0);
	//wrefresh(arena_window);
	info_window = newwin(70, 30, 3, 225);
    refresh();
	//box(info_window, 0, 0);
	//wattron(info_window, A_BOLD);
    mvwprintw(info_window, 0, 0, "Hello info_window");
    wrefresh(info_window);
	mvwprintw(arena_window, 1, 1, "Hello arena_window");
	wrefresh(arena_window);
    getch();

    endwin();
    return 0;
}
*/
/*
int main()
{
	initscr();
	short color_num;
	short color;


	start_color();
	color_num = 32000 % 127;
	init_pair(color_num, COLOR_BLACK, COLOR_RED);
	attron(COLOR_PAIR(color_num));
	mvprintw(1, 1, "Hello arena_window");
	refresh();
	attroff(COLOR_PAIR(color_num));
	short fg;
	short bg;
	pair_content(color_num, &fg, &bg);
	init_pair(15, bg, fg);
	color = COLOR_PAIR(15);
	attron(color);
	mvprintw(2, 2, "Hello 2");
	attroff(color);
	mvprintw(3, 3, "%d", 32000 % COLOR_PAIRS);
	getch();
	endwin();
	return 0;
}
*/


int main(void)
{
	char a[MEM_SIZE];
	i = 0;
	while(i <= MEM_SIZE)
	{
		a[i] = 50;
		++i;
	}
	printf("i=%d   a[i-1]=%d  a[i]=%d\n", i, a[i-1], a[i]);
	return 0;
}