#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <assert.h>

#include "colors.h"
#include "typedef.h"

typedef struct {
    Color *buf;
    i32 height, width;
} Buffer;

void bufferInit(Buffer *buffer, i32 height, i32 width);
Color *bufferGet(Buffer *buffer, i32 y, i32 x);

#endif
