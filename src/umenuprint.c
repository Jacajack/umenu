#include <umenu/umenu.h>
#include <umenu/umenuprint.h>
#include <string.h>
#include <stdio.h>

void umenuPrint( struct umenu *menu, char **buf, int width, int height )
{
	const struct umenuentry *entry, *parent;
	int i, val;

	//Get the entry and its parent
	entry = menu->current;
	parent = umenuParent( entry );

	//Clear the buffer
	for ( i = 0; i < height; i++ )
		memset( buf[i], '-', width );

	if ( menu->editmode || menu->watchmode )
	{
		if ( menu->editmode )
			val = menu->editval;
		else val = *entry->val;

		snprintf( buf[0], width, "%s", entry->header );

		switch ( menu->current->vtype & ~UMENU_EDIT )
		{
			case UMENU_INT:
				snprintf( buf[1], width, "%d", val );
				break;

			case UMENU_LST:
				snprintf( buf[1], width, "%s", umenuList( entry->list, val ) );
				break;
		}

	}
	else
	{
		if ( parent != NULL ) snprintf( buf[0], width, "%s", parent->header );
		snprintf( buf[1], width, "%s", entry->header );
	}

	/*
	const struct umenuentry *parent, *entry;
	const char *str;
	char prefix;
	int i, v;


	if ( menu->editmode || menu->watchmode )
	{
		//Clear the display
		for ( i = 0; i < disph - y; i++ )
		{
			printxy( x, y + i, "%c%-*s", ' ', dispw - 1, "" );
		}

		//Header
		if ( disph - y > 1 )
		{
			//Print the line padded out with spaces
			printxy( x, y, "%s", menu->current->header );
		}

		if ( menu->editmode ) v = menu->editval;
		else v = *menu->current->val;

		switch ( menu->current->vtype & ~UMENU_EDIT )
		{
			case UMENU_INT:
				printxy( x, y + 1, "%d", v );
				break;

			case UMENU_LST:
				printxy( x, y + 1, "%s", umenuList( menu->current->list, v ) );
				break;
		}

	}
	else
	{
		//Get parent and current entries
		parent = umenuParent( menu->current );
		entry = menu->current;

		//Go few nodes back (center current on the display)
		//if ( disph - y > 3 )
		//	for ( i = 0; i < ( disph - y - 1 ) / 2; i++ )
		//		if ( umenuPrev( entry ) != NULL ) entry = umenuPrev( entry );

		//Iterate through the lines
		for ( i = 0; i < disph - y; i++ )
		{
			str = "";
			prefix = ' ';

			//Handle nested menus
			if ( i == 0 && parent != NULL && disph - y != 1 )
			{
				str = parent->header;
				prefix = ':';
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
	*/
}
