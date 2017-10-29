#include <stddef.h>
#include <umenu/umenu.h>
#include <umenu/core.h>



static const struct umenuentry *umenuEnter( struct umenu *menu )
{
	//Validate all pointers
	if ( menu == NULL || menu->tree == NULL || menu->current == NULL ) return NULL;

	if ( menu->current->vtype == UMENU_SUB )
	{
		if ( menu->current[1].depth != UMENU_BOUNDARY && \
			menu->current[1].depth == menu->current->depth + 1 )
		{
			menu->current = menu->current + 1;
		}
	}
	else
	{
		if ( menu->current->vtype & UMENU_EDIT )
			menu->editmode = 1;
		else menu->watchmode = 1;
	}
	return 0;
}

static const struct umenuentry *umenuReturn( struct umenu *menu )
{
	const struct umenuentry *entry;

	//Validate all pointers
	if ( menu == NULL || menu->tree == NULL || menu->current == NULL ) return NULL;

	if ( menu->editmode )
		menu->editmode = 0;
	else if ( menu->watchmode )
		menu->watchmode = 0;
	else
	{
		entry = umenuParent( menu->current );
		if ( entry != NULL )
		{
			menu->current = entry;
			return entry;
		}
	}

	return 0;
}

//Interacts with given menu - passes a keypress
int umenuInteract( struct umenu *menu, int key )
{
	const struct umenuentry *entry;

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
				entry = umenuPrev( menu->current );
				if ( entry != NULL ) menu->current = entry;
				break;

			case UMENU_KEY_DN:
				entry = umenuNext( menu->current );
				if ( entry != NULL ) menu->current = entry;
				break;

			case UMENU_KEY_ENTER:
				if ( menu->current->vtype == UMENU_SUB )
				{
					entry = umenuEnter( menu );
					if ( entry != NULL ) menu->current = entry;
				}
				else if ( menu->current->vtype & UMENU_EDIT ) menu->editmode = 1;
				else menu->watchmode = 1;

				break;

			case UMENU_KEY_RETURN:
				umenuReturn( menu );
				break;

			default:
				break;
		}
	}

	return 0;
}

//Initializes umenu structure
int umenuInit( struct umenu *menu, struct umenuentry *tree, int treesize, struct umenuentry *start )
{
	if ( menu == NULL || tree == NULL ) return 1;

	menu->tree = tree;

	if ( start != NULL && start >= tree && start < tree + treesize ) menu->current = start;
	else menu->current = tree + 1;

	menu->editval = 0;
	menu->editmode = 0;
	menu->watchmode = 0;
	return 0;
}
