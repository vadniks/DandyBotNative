
#include "defs.h"

char NOTHING = -1;
char EMPTY = ' ';
char BLOCK = '#';
char COIN_MIN = '1';
char COIN_MAX = '9';
char ENEMY_MIN = 'a';
char ENEMY_MAX = 'f';
char PLAYER = '!';

char UP = 87;
char LEFT = 65;
char DOWN = 83;
char RIGHT = 68;
char PASS = -1;

inline unsigned
coordsToIndex(unsigned row, unsigned columns, unsigned column)
{ return row * columns + column; }
