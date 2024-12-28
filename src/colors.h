#ifndef COLORS_H
#define COLORS_H

#include "typedef.h"

typedef struct {
    u8 b, g, r, a;
} Color;

#define GOLD  ((Color) {   0, 203, 255, 255 })
#define RED   ((Color) {  55,  41, 230, 255 })
#define BLACK ((Color) {   0,   0,   0, 255 })
#define WHITE ((Color) { 255, 255, 255, 255 })

#endif
