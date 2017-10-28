#include <umenu/core.h>
#include <umenu/umenu.h>
#include <stddef.h>

const struct umenunode *umenuParent( const struct umenunode *node )
{
	int depth = node->depth;
	while ( ( --node )->depth != UMENU_BOUNDARY )
	{
		if ( node->depth == depth - 1 )
		{
			return node;
		}
	}
	return NULL;
}

const struct umenunode *umenuChild( const struct umenunode *node )
{
	int depth = node->depth;
	if ( node->vtype == UMENU_SUB )
	{
		if ( node[1].depth != UMENU_BOUNDARY && node[1].depth == depth + 1 )
		{
			return node;
		}
	}
	return NULL;
}

const struct umenunode *umenuNext( const struct umenunode *entry )
{
	int depth;

	//Validate all pointers
	if ( entry == NULL ) return NULL;

	//Remember the depth we are looking for
	depth = entry->depth;

	//Iterate through the nodes
	while ( ( ++entry )->depth != UMENU_BOUNDARY )
	{
		//The node we found becomes the current one
		if ( entry->depth == depth )
		{
			return entry;
		}
	}

	return NULL;
}

const struct umenunode *umenuPrev( const struct umenunode *entry )
{
	int depth;

	//Validate all pointers
	if ( entry == NULL ) return NULL;

	//Remember the depth we are looking for
	depth = entry->depth;

	//Iterate through the nodes
	while ( ( --entry )->depth != UMENU_BOUNDARY )
	{
		//The node we found becomes the current one
		if ( entry->depth == depth )
		{
			return entry;
		}
	}

	return NULL;
}
