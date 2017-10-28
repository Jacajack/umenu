#ifndef UMENU_H
#define UMENU_H
#include <inttypes.h>
#include "core.h"

//Key definitions
#define UMENU_KEY_UP     1
#define UMENU_KEY_DN     2
#define UMENU_KEY_ENTER  3
#define UMENU_KEY_RETURN 4


struct umenu
{
	const struct umenunode *tree;
	const struct umenunode *current;

	//Value of currently edited field
	int editval;

	//Flags
	unsigned int editmode : 1;
	unsigned int watchmode : 1;
	unsigned int : 0;
};

//Prototypes
extern int umenuInteract( struct umenu *menu, int key );
extern int umenuInit( struct umenu *menu, struct umenunode *tree, int treesize, struct umenunode *start );
#endif
