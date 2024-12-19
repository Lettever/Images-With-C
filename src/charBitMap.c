#include "charBitMap.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FILE_PATH "./src/letters.txt"
#define MAX_BUFFER_SIZE 16
#define MAX_CHARS_LEN 10

u8 charMap[256][8][5];

int hexDigitToNum(char ch) {
    if (isdigit(ch)) return ch - '0';
    if (islower(ch)) return ch - 'a' + 10;
    if (isupper(ch)) return ch - 'A' + 10;
    fprintf(stderr, "ERROR: >%c< is an unacceptable character\n", ch);
    assert(0);
}

void initCharMap() {
    // To initialize the map we'll be reading from 'letters.txt'
    // The file has an encoding of type CX0X1X2X3X4
    // Where C is the character and all X's are 2 hexadecimals characters that say if a bit is on or off in a column
    // For example:
    // AFC121112FC
    // C = A, X0 = FC, X1 = 12, X2 = 11, X3 = 12, X4 = FC
    // Decoding to binary
    // X0 = 1 1 1 1 1 1 0 0
    // X1 = 0 0 0 1 0 0 1 0 
    // X1 = 0 0 0 1 0 0 0 1 
    // X3 = 0 0 0 1 0 0 1 0 
    // X4 = 1 1 1 1 1 1 0 0
    // If you turn that thing counter-clockwise, you will see an 'A'


    char buffer[MAX_BUFFER_SIZE + 1];
    FILE *f = fopen(FILE_PATH, "r");  
    
    if (f == NULL) {
        fprintf(stderr, "Could not open '%s' file\n", FILE_PATH);
        fprintf(stderr, "Could not initialize charBitMap");
        exit(1);
    }

    while (fgets(buffer, MAX_BUFFER_SIZE, f) != NULL) {
        char ch = buffer[0];
        for (u8 c = 0; c < MAX_CHARS_LEN; c += 2) {
            u16 n = hexDigitToNum(buffer[c + 1]) * 16 + hexDigitToNum(buffer[c + 2]);
            printf("%d %x\n", n, n);
            int j = c / 2;
            for (u8 i = 0; i < 8; i++) {
                printf("%d", (n >> (7 - i)) & 1);
                charMap[ch][7 - i][j] = (n >> (7 - i)) & 1;
            }
            printf("\n");
        }
    }

    fclose(f);
    printf("ok\n");
}