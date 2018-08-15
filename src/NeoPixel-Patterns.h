
#ifndef NeoPixelPatterns_h
#define NeoPixelPatterns_h

#include <Arduino.h>

typedef uint32_t        color_t;
typedef uint8_t         state_t;

typedef int8_t          direction_t;
typedef unsigned long   millis_t;

#define COLOR(r,g,b)    ((color_t)(((uint32_t)r<<16)|((uint16_t)g<<8)|b))
#define RED(color)      ((color>>16)&0xff)
#define GREEN(color)    ((color>>8)&0xff)
#define BLUE(color)     (color&0xff)
#define DIMCOLOR(color) (COLOR(RED(color)>>1,GREEN(color)>>1,BLUE(color)>>1))

#define COLOR_OFF       (COLOR(0,0,0))
#define COLOR_WHITE     (COLOR(255,255,255))
#define COLOR_RED       (COLOR(255,0,0))
#define COLOR_GREEN     (COLOR(0,255,0))
#define COLOR_BLUE      (COLOR(0,0,255))

#include "NeoPixelController.h"
#include "NeoPixelPattern.h"
#include "WipeNeoPixelPattern.h"
#include "RainbowNeoPixelPattern.h"
#include "ChaseNeoPixelPattern.h"

#endif
