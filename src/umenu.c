#include <stddef.h>
#include <umenu.h>

static const struct umenunode *umenuNext( struct umenu *menu )
{
	int i, depth;

	if ( menu == NULL ) return NULL;

	depth = menu->tree[menu->current].depth;

	for ( i = menu->current + 1; i < menu->treesize; i++ )
	{
		if ( menu->tree[i].depth == depth )
		{
			menu->current = i;
			return &menu->tree[i];
		}
	}
}

//Interacts with given menu - passes a keypress
int umenuInteract( struct umenu *menu, int key )
{
	return 0;
}
