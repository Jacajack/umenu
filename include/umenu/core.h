#ifndef UMENU_CORE_H
#define UMENU_CORE_H

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

//Menu node
struct umenuentry
{
	int depth;		    //Node's depth
	const char *header; //Header text
	int vtype;		    //Affected value type
	void *vptr;		    //Pointer to value affected by given setting
	int vcnt;		    //List option count
	void *vlist; 	    //List values
};

//Prototypes
extern const struct umenuentry *umenuParent( const struct umenuentry *entry );
extern const struct umenuentry *umenuChild( const struct umenuentry *entry );
extern const struct umenuentry *umenuNext( const struct umenuentry *entry );
extern const struct umenuentry *umenuPrev( const struct umenuentry *entry );

#endif
