#ifndef CHAR_BIT_MAP_H
#define CHAR_BIT_MAP_H

#include "typedef.h"

typedef u8 CharBitMap[8][5];

extern u8 charMap[256][8][5];
// for the fonts: https://departuremono.com/
void initCharMap();

#endif