
#pragma once

/** object ids */
extern char NOTHING;
extern char EMPTY;
extern char BLOCK;
extern char COIN_MIN;
extern char COIN_MAX;
extern char ENEMY_MIN;
extern char ENEMY_MAX;
extern char PLAYER;

/** action ids */
extern char UP;
extern char LEFT;
extern char DOWN;
extern char RIGHT;
extern char PASS;

/** Converts row and column coordinates to index of an object */
unsigned coordsToIndex(unsigned row, unsigned columns, unsigned column);

/** Checks whether the given object is a coin */
int isCoin(char object);

/** Checks whether the given object is an enemy */
int isEnemy(char object);
