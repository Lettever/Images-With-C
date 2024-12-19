#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "colors.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#pragma pack(push, 1) // Ensure structures are packed tightly in memory

// BMP file header
typedef struct {
    u16 bfType;      // File type ('BM')
    u32 bfSize;      // File size in bytes
    u16 bfReserved1; // Reserved
    u16 bfReserved2; // Reserved
    u32 bfOffBits;   // Offset to pixel data
} BMPFileHeader;

// BMP info header
typedef struct {
    u32 biSize;          // Info header size
    i32 biWidth;         // Image width
    i32 biHeight;        // Image height
    u16 biPlanes;        // Number of color planes (must be 1)
    u16 biBitCount;      // Bits per pixel (24 for RGB)
    u32 biCompression;   // Compression type (0 for no compression)
    u32 biSizeImage;     // Image data size (can be 0 for uncompressed images)
    i32 biXPelsPerMeter; // Horizontal resolution (pixels per meter)
    i32 biYPelsPerMeter; // Vertical resolution (pixels per meter)
    u32 biClrUsed;       // Number of colors in palette (0 for no palette)
    u32 biClrImportant;  // Important colors (0 means all are important)
} BMPInfoHeader;

#pragma pack(pop)

typedef struct {
    Color *buf;
    i32 height, width;
} Buffer;

void drawCharacter(Buffer *buffer, int y, int x, Color color, char ch);
void drawText(Buffer *buffer, int y, int x, Color color, const char* text);
void drawLine(Buffer *buffer, int y1, int x1, int y2, int x2);

void buffer_init(Buffer *buffer, i32 height, i32 width) {
    buffer->height = height;
    buffer->width = width;
    buffer->buf = calloc(height * width, sizeof(*buffer->buf));
    assert((buffer->buf != NULL) && "Could not alocate buffer, download more RAM\n");
}

int main() {
    i32 width = 256, height = 256;
    const char *filename = "output_image.bmp";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Could not open file for writing");
        return 1;
    }

    BMPFileHeader fileHeader = {
        .bfType = 0x4D42, // "BM"
        .bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader),
        .bfSize = fileHeader.bfOffBits + (width * height * sizeof(Color)), // Header + pixel data
        .bfReserved1 = 0,
        .bfReserved2 = 0,
    };
    BMPInfoHeader infoHeader = {
        .biSize = sizeof(BMPInfoHeader),
        .biWidth = width,
        .biHeight = -height, // Negative height for top-down row order
        .biPlanes = 1,
        .biBitCount = 8 * sizeof(Color),
        .biCompression = 0,
        .biSizeImage = width * height * sizeof(Color),
        .biXPelsPerMeter = 2835, // 72 DPI
        .biYPelsPerMeter = 2835, // 72 DPI
        .biClrUsed = 0,
        .biClrImportant = 0,
    };

    fwrite(&fileHeader, sizeof(fileHeader), 1, file);
    fwrite(&infoHeader, sizeof(infoHeader), 1, file);
    
    Buffer buffer = { 0 };
    buffer_init(&buffer, height, width);

    for (int y = 0; y < height; y++) {
       for (int x = 0; x < width; x++) {
           if (y < height / 2) buffer.buf[y * width + x] = (Color) { 255, 0, 0, 0 };
           else buffer.buf[y * width + x] = RED;
       }
    }

    for (int y = height / 2 - 50; y < height / 2 + 50; y++) {
       for (int x = width / 2 - 50; x < width / 2 + 50; x++) {
           buffer.buf[y * width + x] = GOLD;
       }
    }

    fwrite(buffer.buf, sizeof(*buffer.buf), buffer.height * buffer.width, file);
    fclose(file);
    free(buffer.buf);
    printf("Image created: %s\n", filename);
    return 0;
}

void drawCharacter(Buffer *buffer, int y, int x, Color color, char ch) {
    assert(0 && "TODO");
}

void drawText(Buffer *buffer, int y, int x, Color color, const char* text) {
    assert(0 && "TODO");
}

void drawLine(Buffer *buffer, int y1, int x1, int y2, int x2) {
    assert(0 && "TODO");
}

// 7 * 8
// for the fonts: https://departuremono.com/