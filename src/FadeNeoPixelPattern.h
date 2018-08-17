
#ifndef FadeNeoPixelPattern_h
#define FadeNeoPixelPattern_h

#include "NeoPixelPattern.h"

class FadeNeoPixelPattern : public NeoPixelPattern {

public:

    static const uint8_t SINGLE = 0;
    static const uint8_t REPEAT = 1;
    static const uint8_t PING_PONG = 2;
    
    color_t color1;
    color_t color2;
    uint16_t steps;
    uint8_t mode;
    int16_t index;
    bool forward;
    
    FadeNeoPixelPattern() {}

    void setup(color_t _color1, color_t _color2, uint16_t _steps, unsigned long _interval, uint8_t _mode = SINGLE) {
        color1 = _color1;
        color2 = _color2;
        steps = _steps;
        interval = _interval;
        mode = _mode;
        reset();
    }
    
    virtual void reset() {
        index = 0;
        forward = true;
    }
    
    virtual void update() {
        uint8_t red, green, blue;
        
        red = ((RED(color1) * (steps - index)) + (RED(color2) * index)) / steps;
        green = ((GREEN(color1) * (steps - index)) + (GREEN(color2) * index)) / steps;
        blue = ((BLUE(color1) * (steps - index)) + (BLUE(color2) * index)) / steps;
        controller->setSegmentColor(COLOR(red, green, blue), segment);

        if (forward) {
            index++;
            if (index >= steps) {
                if (mode & PING_PONG) {
                    index = steps - 1;
                    forward = false;
                } else if (mode & REPEAT) {
                    index = 0;
                    looped = true;
                } else {
                    complete = true;
                }
            }
        } else {
            index--;
            if (index < 0) {
                if (mode & REPEAT) {
                    index = 0;
                    forward = true;
                    looped = true;
                } else {
                    complete = true;
                }
            }
        }
    }
    
};

#endif
