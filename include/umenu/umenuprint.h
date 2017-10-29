#ifndef UMENU_PRINT_H
#define UMENU_PRINT_H

extern void umenuPrint( struct umenu *menu, int dispw, int disph, int x, int y, int (*printxy)( int x, int y, const char *format, ... ) );

#endif
