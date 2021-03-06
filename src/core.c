#include <umenu/core.h>
#include <umenu/umenu.h>
#include <stddef.h>

//Returns pointer to parent menu entry or NULL if there's no parent
const struct umenuentry *umenuParent( const struct umenuentry *entry )
{
	int depth;
	if ( entry == NULL ) return NULL;

	//Iterate till boundary encounter
	depth = entry->depth;
	while ( ( --entry )->depth != UMENU_BOUNDARY )
	{
		if ( entry->depth == depth - 1 )
			return entry;
	}
	return NULL;
}

//Returns pointer to first child of menu entry or NULL if such doesn't exist
const struct umenuentry *umenuChild( const struct umenuentry *entry )
{
	int depth;
	if ( entry == NULL ) return NULL;

	//Check next entry
	depth = entry->depth;
	if ( entry->vtype == UMENU_SUB )
	{
		if ( entry[1].depth != UMENU_BOUNDARY && entry[1].depth == depth + 1 )
			return entry + 1;
	}
	return NULL;
}

//Returns next entry of the same depth or NULL if such doesn't exist
const struct umenuentry *umenuNext( const struct umenuentry *entry )
{
	int depth;
	if ( entry == NULL ) return NULL;

	//Iterate till boundary encounter
	depth = entry->depth;
	while ( ( ++entry )->depth != UMENU_BOUNDARY )
	{
		if ( entry->depth < depth ) break;
		if ( entry->depth == depth )
			return entry;
	}
	return NULL;
}

//Returns previous entry of the same depth or NULL if such doesn't exist
const struct umenuentry *umenuPrev( const struct umenuentry *entry )
{
	int depth;
	if ( entry == NULL ) return NULL;

	//Iterate till boundary encounter
	depth = entry->depth;
	while ( ( --entry )->depth != UMENU_BOUNDARY )
	{
		if ( entry->depth < depth ) break;
		if ( entry->depth == depth )
			return entry;
	}

	return NULL;
}

//Returns string containg name of the nth item from the list
const char *umenuList( const char *list, int n )
{
	//Does list point to the start of new item?
	int newitem = 1;

	//Double NUL is list boundary
	while ( list[0] != 0 || list[1] != 0 )
	{
		if ( newitem && n-- == 0 ) return list;

		if ( list[0] == 0 )
			newitem = 1;
		else
			newitem = 0;

		list++;
	}

	return NULL;
}
