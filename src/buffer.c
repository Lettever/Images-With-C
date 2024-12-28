#include "buffer.h"

void bufferInit(Buffer *buffer, i32 height, i32 width) {
    buffer->height = height;
    buffer->width = width;
    buffer->buf = calloc(height * width, sizeof(*buffer->buf));
    assert((buffer->buf != NULL) && "Could not alocate buffer, download more RAM\n");
}

Color *bufferGet(Buffer *buffer, i32 y, i32 x) {
    return buffer->buf + y * buffer->width + x;
}

