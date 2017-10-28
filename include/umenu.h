#ifndef UMENU_H
#define UMENU_H
#include <inttypes.h>

//Value type macros + edit macro
#define UMENU_NOVAL 0
#define UMENU_INT   1
#define UMENU_CHR   2
#define UMENU_LST   3
#define UMENU_LINT  4
#define UMENU_LCHR  5
#define UMENU_EDIT  16

//Key definitions
#define UMENU_KEY_UP    1
#define UMENU_KEY_DN    2
#define UMENU_KEY_ENTER 3
#define UMENU_KEY_BACK  4

//Menu node
struct umenunode
{
	int depth;		//Node's depth
	const char *header; //Header text
	int vtype;		//Affected value type
	void *vptr;		//Pointer to value affected by given setting
	int vcnt;		//List option count
	void *vlist; 	//List values
};

struct umenu
{
	const struct umenunode *tree;
	int treesize;
	struct umenunode *current, *parent;

	int editval;

	//Flags
	unsigned int editmode : 1;
	unsigned int : 0;
};

extern int umenuInteract( struct umenu *menu, int key );
#endif
