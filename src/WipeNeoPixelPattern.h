
#ifndef WipeNeoPixelPattern_h
#define WipeNeoPixelPattern_h

#include "NeoPixel-Patterns.h"

class WipeNeoPixelPattern : public NeoPixelPattern {

public:

    static const direction_t FORWARD = 1;
    static const direction_t REVERSE = -1;
    
    color_t color;
    millis_t interval;
    direction_t direction;
    int16_t index;
    
    WipeNeoPixelPattern(color_t _color, millis_t _interval, direction_t _direction = FORWARD) :
        NeoPixelPattern(),
        color(_color),
        interval(_interval),
        direction(_direction),
        index(0) {}

    void setup(color_t _color, millis_t _interval, direction_t _direction = FORWARD) {
        color = _color;
        interval = _interval;
        direction = _direction;
        reset();
    }
    
    virtual void reset() {
        index = -1;
    }
    
    virtual void update() {
        if (index == -1) {
            index = (direction > 0) ? 0 : controller->numPixels() - 1;
        }
        
        controller->setPixelColor(index, color);
        
        index += direction;
        if ((index >= controller->numPixels()) || (index < 0)) {
            state = COMPLETE;
        }
    }
    
};

#endif
