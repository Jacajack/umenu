#ifndef UMENU_H
#define UMENU_H
#include <inttypes.h>

//Value type macros
#define UMENU_NOSET
#define UMENU_INT
#define UMENU_CHR
#define UMENU_LST
#define UMENU_LINT
#define UMENU_LCHR

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
	int current;
	int parent;

	int editval;

	//Flags
	unsigned int editmode;
	
};
#endif

