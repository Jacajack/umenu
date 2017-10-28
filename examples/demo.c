#include <stdio.h>
#include <umenu.h>
#include <ctype.h>
#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

//The menu tree
struct umenunode menutree[] =
{
	{ 0, "my menu", UMENU_SUB, NULL, 0, NULL },
		{ 1, "some submenu 0", UMENU_SUB, NULL, 0, NULL },
		{ 1, "some submenu 1", UMENU_SUB, NULL, 0, NULL },
		{ 1, "some submenu 2", UMENU_SUB, NULL, 0, NULL },
		{ 1, "some submenu 3", UMENU_SUB, NULL, 0, NULL },
			{ 2, "and even deeper submenu", UMENU_SUB, NULL, 0, NULL },
	{ 0, "another option", UMENU_SUB, NULL, 0, NULL },
	{ 0, "is cool", UMENU_SUB, NULL, 0, NULL },
	{ 0, "and lovely", UMENU_SUB, NULL, 0, NULL },
};
#define MENU_SIZE ( sizeof( menutree ) / sizeof( menutree[0] ) ) 

int alive = 1;

void quit( int dummy )
{
	curs_set( 1 );
	echo( );
	endwin( );
	exit( 0 );
}

int main( int argc, char **argv )
{
	int c = 0;
	char buf[512];
	int maxx, maxy;
	
	struct umenu menu;
	umenuInit( &menu, menutree, MENU_SIZE, NULL );
	
	signal( SIGINT, quit );
	
	initscr( );
	curs_set( 0 );
	noecho( );
	start_color( );
	keypad( stdscr, TRUE );
	
	//Create virtual LCD
	int lcdx = 16, lcdy = 2;
	init_pair( 1, COLOR_WHITE, COLOR_BLUE );
	init_pair( 2, COLOR_WHITE, COLOR_BLACK );
	init_pair( 3, COLOR_WHITE, COLOR_WHITE );
	getmaxyx( stdscr, maxy, maxx );
	WINDOW *lcdframe = newwin( lcdy + 2, lcdx + 2, ( maxy - lcdy - 2 ) / 2, ( maxx - lcdx - 2 ) / 2 );
	WINDOW *lcd = newwin( lcdy, lcdx, ( maxy - lcdy ) / 2, ( maxx - lcdx ) / 2 );
	wbkgd( stdscr, COLOR_PAIR( 3 ) );
	wbkgd( lcdframe, COLOR_PAIR( 2 ) );
	wbkgd( lcd, COLOR_PAIR( 1 ) );

	while ( 1 )
	{
		//Update LCD
		werase( lcd );
		snprintf( buf, 512, "%s", menu.current->header );
		mvwprintw( lcd, 0, 0, "%s", buf );
		mvwprintw( lcdframe, 0, ( lcdx + 2 ) / 2 - 6, "LCD SIM 3000" );
		wrefresh( stdscr );
		wrefresh( lcdframe );
		wrefresh( lcd );
		
		c = tolower( getch( ) );
		
		switch ( c )
		{
			case KEY_DOWN:
				umenuInteract( &menu, UMENU_KEY_DN );
				break;
				
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
	}
	
	
}
