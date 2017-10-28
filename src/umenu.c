#include <stddef.h>
#include <umenu.h>

static const struct umenunode *umenuNext( struct umenu *menu )
{
	struct umenunode *entry;
	int depth;

	//Validate all pointers
	if ( menu == NULL || menu->tree == NULL || menu->current == NULL ) return NULL;

	//Remember the depth we are looking for
	depth = menu->current->depth;

	//Iterate through the nodes
	for ( entry = menu->current + 1; entry < menu->tree + menu->treesize; entry++ )
	{
		//The node we found becomes the current one
		if ( entry->depth == depth )
		{
			menu->current = entry;
			break;
		}
	}

	return menu->current;
}

static const struct umenunode *umenuPrev( struct umenu *menu )
{
	struct umenunode *entry;
	int depth;

	//Validate all pointers
	if ( menu == NULL || menu->tree == NULL || menu->current == NULL ) return NULL;

	//Remember the depth we are looking for
	depth = menu->current->depth;

	//Iterate through the preceding nodes
	for ( entry = menu->current - 1; entry >= menu->tree; entry-- )
	{
		//The node we found becomes the current one
		if ( entry->depth == depth )
		{
			menu->current = entry;
			break;
		}
	}

	return menu->current;
}

//Interacts with given menu - passes a keypress
int umenuInteract( struct umenu *menu, int key )
{
	if ( menu == NULL ) return 1;

	//Browse menu or change value - depending on whether edit mode is enabled
	if ( menu->editmode )
	{

	}
	else
	{
		switch ( key )
		{
			case UMENU_KEY_UP:
				umenuPrev( menu );
				break;

			case UMENU_KEY_DN:
				umenuNext( menu );
				break;

			default:
				break;
		}
	}

	return 0;
}
