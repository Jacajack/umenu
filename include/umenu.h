#ifndef UMENU_H
#define UMENU_H
#include <inttypes.h>

//Value type macros + edit macro
#define UMENU_SUB   0
#define UMENU_INT   1
#define UMENU_CHR   2
#define UMENU_LST   3
#define UMENU_LINT  4
#define UMENU_LCHR  5
#define UMENU_EDIT  16

//Boundaries
#define UMENU_BOUNDARY ( -1 )
#define UMENU_ROOT UMENU_BOUNDARY
#define UMENU_END UMENU_BOUNDARY

//Key definitions
#define UMENU_KEY_UP     1
#define UMENU_KEY_DN     2
#define UMENU_KEY_ENTER  3
#define UMENU_KEY_RETURN 4

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
