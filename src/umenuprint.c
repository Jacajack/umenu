#include <umenu/umenu.h>
#include <umenu/umenuprint.h>
#include <string.h>
#include <stdio.h>

void umenuPrint( struct umenu *menu, int dispw, int disph, int x, int y, int (*printxy)( int x, int y, const char *format, ... ) )
{
	const struct umenunode *parent, *entry;
	int i;
	const char *str;
	char prefix;


	//Get parent entry
	parent = umenuParent( menu->current );

	entry = menu->current;

	//Go few nodes back (center current on the display)
	if ( disph - y > 3 )
		for ( i = 0; i < ( disph - y - 1 ) / 2; i++ )
			if ( umenuPrev( entry ) != NULL ) entry = umenuPrev( entry );

	//Iterate through the lines
	for ( i = 0; i < disph - y; i++ )
	{
		str = "";
		prefix = ' ';

		//Handle nested menus
		if ( i == 0 && parent != NULL && disph - y != 1 )
		{
			str = parent->header;
			prefix = '-';
		}
		else
		{
			//Display entry
			if ( entry != NULL )
			{
				//Choose proper prefix
				if ( entry == menu->current )
					prefix = '>';
				else switch ( entry->vtype )
				{
					case UMENU_SUB:
						prefix = ' ';
						break;

					default:
						prefix = ' ';
						break;
				}



				str = entry->header;

			}
			entry = umenuNext( entry );
		}

		//Print the line padded out with spaces
		printxy( x, y + i, "%c%-*s", prefix, dispw - 1, str );
	}

}
