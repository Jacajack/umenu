#include <stdio.h>
#include <umenu/umenu.h>
#include <umenu/umenuprint.h>
#include <ctype.h>
#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

int lcdsimv = 3000;
int foreground = 7;
int background = 4;

int clicks = 0;
WINDOW *lcd;
WINDOW *lcdframe;

//The menu tree
struct umenuentry menutree[] =
{
	{ UMENU_ROOT },
	{ 0, "Nested menus", UMENU_SUB },
		{ 1, "And one more", UMENU_SUB },
			{ 2, "And moore...", UMENU_SUB },
	{ 0, "Integers", UMENU_SUB },
		{ 1, "Key counter", UMENU_INT, &clicks, 0, 0, NULL },
		{ 1, "LCD version", UMENU_INT | UMENU_EDIT, &lcdsimv, 2990, 3010, NULL },
	{ 0, "Lists", UMENU_SUB },
		{ 1, "Foreground", UMENU_LST | UMENU_EDIT, &foreground, 0, 7, "black\0red\0green\0yellow\0blue\0magenta\0cyan\0white\0" },
		{ 1, "Background", UMENU_LST | UMENU_EDIT, &background, 0, 7, "black\0red\0green\0yellow\0blue\0magenta\0cyan\0white\0" },
	{ UMENU_END }
};
#define MENU_SIZE ( sizeof( menutree ) / sizeof( menutree[0] ) )

//A routine to nicely exit ncurses mode
void quit( int dummy )
{
	curs_set( 1 );
	echo( );
	endwin( );
	exit( 0 );
}

int main( int argc, char **argv )
{
	int lcdx = 16, lcdy = 4, i;
	char **lcdbuf;
	int maxx, maxy;
	struct umenu menu;

	lcdbuf = (char**) malloc( lcdy * sizeof( char*) );
	for ( i = 0; i < 4; i++ )
		lcdbuf[i] = (char*) malloc( lcdx * sizeof( char ) );

	//Quit on Ctrl+C
	signal( SIGINT, quit );

	//Init ncurses
	initscr( );
	curs_set( 0 );
	noecho( );
	start_color( );
	keypad( stdscr, TRUE );

	//Create virtual LCD
	init_pair( 2, COLOR_WHITE, COLOR_BLACK );
	init_pair( 3, COLOR_WHITE, COLOR_WHITE );
	getmaxyx( stdscr, maxy, maxx );
	lcdframe = newwin( lcdy + 2, lcdx + 2, ( maxy - lcdy - 2 ) / 2, ( maxx - lcdx - 2 ) / 2 );
	lcd = newwin( lcdy, lcdx, ( maxy - lcdy ) / 2, ( maxx - lcdx ) / 2 );
	wbkgd( stdscr, COLOR_PAIR( 3 ) );
	wbkgd( lcdframe, COLOR_PAIR( 2 ) );
	wbkgd( lcd, COLOR_PAIR( 1 ) );

	//Init our menu structure
	umenuInit( &menu, menutree, MENU_SIZE, menutree + 2 );

	while ( 1 )
	{
		//Update LCD
		init_pair( 1, foreground, background );
		umenuPrint( &menu, lcdbuf, lcdx, lcdy );
		for ( i = 0; i < lcdy; i++ ) mvwprintw( lcd, i, 0, "%-16s", lcdbuf[i] );

		mvwprintw( lcdframe, 0, ( lcdx + 2 ) / 2 - 6, "LCD SIM %d", lcdsimv );
		wrefresh( stdscr );
		wrefresh( lcdframe );
		wrefresh( lcd );

		//Interpret keyboard actions
		switch ( tolower( getch( ) ) )
		{
			case KEY_LEFT:
			case KEY_DOWN:
				umenuInteract( &menu, UMENU_KEY_DN );
				break;

			case KEY_RIGHT:
			case KEY_UP:
				umenuInteract( &menu, UMENU_KEY_UP );
				break;

			case 10:
				umenuInteract( &menu, UMENU_KEY_ENTER );
				break;

			case KEY_BACKSPACE:
				umenuInteract( &menu, UMENU_KEY_RETURN );
				break;

			case 'q':
			case '\\':
				quit( 1 );
				break;
		}

		//Count keypresses
		clicks++;
	}


}
