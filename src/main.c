#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "buffer.h"
#include "colors.h"
#include "charBitMap.h"
#include "typedef.h"

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

void drawCharacter(Buffer *buffer, int y, int x, Color color, char ch);
void drawText(Buffer *buffer, int y, int x, Color color, const char* text);
void drawLine(Buffer *buffer, int y1, int x1, int y2, int x2, Color color);

int main() {
    initCharMap();
    u8 A[8][5];
    /*
    for (int ch = 'A'; ch <= 'Z'; ch++) {
        memcpy(A, charMap[ch], sizeof(CharBitMap));
        printf("%c:\n", ch);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 5; j++) {
                if (A[i][j] == 1) printf("#");
                else printf(" ");
            }
            printf("\n");
        }
    }

    for (int ch = 'a'; ch <= 'z'; ch++) {
        memcpy(A, charMap[ch], sizeof(CharBitMap));
        printf("%c:\n", ch);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 5; j++) {
                if (A[i][j] == 1) printf("%c", '#');
                else printf(" ");
            }
            printf("\n");
        }
    }
    */
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
    bufferInit(&buffer, height, width);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            buffer.buf[y * width + x] = WHITE;
        }
    }
    
    memcpy(A, charMap['A'], sizeof(CharBitMap));
    int dy = 50, dx = 50;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 5; x++) {
            Color *c = bufferGet(&buffer, y + dy, x + dx);
            if (A[y][x] == 1) {
                *c = BLACK;
            } else {
                *c = RED;
            }
        }
        //printf("\n");
    }
    
    fwrite(buffer.buf, sizeof(*buffer.buf), buffer.height * buffer.width, file);
    fclose(file);
    free(buffer.buf);
    printf("Image created: %s\n", filename);
    return 0;
}



void drawCharacter(Buffer *buffer, int y, int x, Color color, char ch) {
    (void) buffer;
    (void) y;
    (void) x;
    (void) color;
    (void) ch;
    assert(0 && "TODO");
}

void drawText(Buffer *buffer, int y, int x, Color color, const char* text) {
    (void) buffer;
    (void) y;
    (void) x;
    (void) color;
    (void) text;
    assert(0 && "TODO");
}

void drawLine(Buffer *buffer, int y1, int x1, int y2, int x2, Color color) {
    (void) buffer;
    (void) y1;
    (void) x1;
    (void) y2;
    (void) x2;
    (void) color;
    assert(0 && "TODO");
}

/*
0 0 1 0 0
0 1 0 1 0
1 0 0 0 1
1 0 0 0 1
1 1 1 1 1
1 0 0 0 1
1 0 0 0 1
1 0 0 0 1

1 1 1 1 1 1 0 0 -> FC
0 0 0 1 0 0 1 0 -> 12
0 0 0 1 0 0 0 1 -> 11
0 0 0 1 0 0 1 0 -> 11
1 1 1 1 1 1 0 0 -> FC
*/

/*
j
40 -> 0 1 0 0 0 0 0 0
84 -> 1 0 0 0 0 1 0 0
84 -> 1 0 0 0 0 1 0 0
7D -> 0 1 1 1 1 1 0 1
00 -> 0 0 0 0 0 0 0 0

___#_
_____
_###_
___#_
___#_
___#_
#__#_
_###_

 */
