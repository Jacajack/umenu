#include <stddef.h>
#include <umenu.h>

static const struct umenunode *parentof( struct umenu *menu, const struct umenunode *node )
{
	const struct umenunode *entry = menu->current;
	while ( ( --entry )->depth != UMENU_BOUNDARY )
	{
		if ( entry->depth == menu->current->depth - 1 )
		{
			return entry;
		}
	}
	return NULL;
}

static const struct umenunode *umenuNext( struct umenu *menu )
{
	const struct umenunode *entry;
	int depth;

	//Validate all pointers
	if ( menu == NULL || menu->tree == NULL || menu->current == NULL || menu->editmode || menu->watchmode ) return NULL;

	//Remember the depth we are looking for
	depth = menu->current->depth;

	//Iterate through the nodes
	entry = menu->current;
	while ( ( ++entry )->depth != UMENU_BOUNDARY )
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
	const struct umenunode *entry;
	int depth;

	//Validate all pointers
	if ( menu == NULL || menu->tree == NULL || menu->current == NULL || menu->editmode || menu->watchmode ) return NULL;

	//Remember the depth we are looking for
	depth = menu->current->depth;

	//Iterate through the preceding nodes
	entry = menu->current;
	while ( ( --entry )->depth != UMENU_BOUNDARY )
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

static const struct umenunode *umenuEnter( struct umenu *menu )
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

static const struct umenunode *umenuReturn( struct umenu *menu )
{
	const struct umenunode *entry;

	//Validate all pointers
	if ( menu == NULL || menu->tree == NULL || menu->current == NULL ) return NULL;

	if ( menu->editmode )
		menu->editmode = 0;
	else if ( menu->watchmode )
		menu->watchmode = 0;
	else
	{
		entry = parentof( menu, menu->current );
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

			case UMENU_KEY_ENTER:
				umenuEnter( menu );
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
int umenuInit( struct umenu *menu, struct umenunode *tree, int treesize, struct umenunode *start )
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
