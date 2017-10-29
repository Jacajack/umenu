#include <stdio.h>
#include <umenu/umenu.h>
#include <umenu/umenuprint.h>
#include <ctype.h>
#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

int alive = 1;
int clicks = 0;
WINDOW *lcd;
WINDOW *lcdframe;

//The menu tree
struct umenunode menutree[] =
{
	{ UMENU_ROOT },
	//{ 0, "clicks", UMENU_INT, &clicks, 0, NULL },
	{ 0, "my menu", UMENU_SUB, NULL, 0, NULL },
		{ 1, "some submenu 0", UMENU_SUB, NULL, 0, NULL },
		{ 1, "some submenu 1", UMENU_SUB, NULL, 0, NULL },
		{ 1, "some submenu 2", UMENU_SUB, NULL, 0, NULL },
		{ 1, "some submenu 3", UMENU_SUB, NULL, 0, NULL },
			{ 2, "and even deeper submenu", UMENU_SUB, NULL, 0, NULL },
	{ 0, "another option", UMENU_SUB, NULL, 0, NULL },
	{ 0, "is cool", UMENU_SUB, NULL, 0, NULL },
	{ 0, "and lovely", UMENU_SUB, NULL, 0, NULL },
	{ UMENU_END }
};
#define MENU_SIZE ( sizeof( menutree ) / sizeof( menutree[0] ) ) 

int lcdprint( int x, int y, const char *format, ... )
{
	va_list args;
	va_start( args, format );
	wmove( lcd, y, x );
	vwprintw( lcd, format, args );
	va_end( args );
	return 0;
}

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
	umenuInit( &menu, menutree, MENU_SIZE, menutree + 2 );
	
	signal( SIGINT, quit );
	
	initscr( );
	curs_set( 0 );
	noecho( );
	start_color( );
	keypad( stdscr, TRUE );
	
	//Create virtual LCD
	int lcdx = 16, lcdy = 4;
	init_pair( 1, COLOR_WHITE, COLOR_BLUE );
	init_pair( 2, COLOR_WHITE, COLOR_BLACK );
	init_pair( 3, COLOR_WHITE, COLOR_WHITE );
	getmaxyx( stdscr, maxy, maxx );
	lcdframe = newwin( lcdy + 2, lcdx + 2, ( maxy - lcdy - 2 ) / 2, ( maxx - lcdx - 2 ) / 2 );
	lcd = newwin( lcdy, lcdx, ( maxy - lcdy ) / 2, ( maxx - lcdx ) / 2 );
	wbkgd( stdscr, COLOR_PAIR( 3 ) );
	wbkgd( lcdframe, COLOR_PAIR( 2 ) );
	wbkgd( lcd, COLOR_PAIR( 1 ) );

	while ( 1 )
	{
		//Update LCD
		//werase( lcd );
		snprintf( buf, 512, "%s", menu.current->header );
		//mvwprintw( lcd, 0, 0, "%s", buf );
		umenuPrint( &menu, lcdx, lcdy, 0, 0, lcdprint ); 
		//lcdprint( 0, 0, "dupa" );
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
		
		clicks++;
	}
	
	
}
