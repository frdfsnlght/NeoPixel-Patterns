
#ifndef ChaseNeoPixelPattern_h
#define ChaseNeoPixelPattern_h

#include "NeoPixel-Patterns.h"

class ChaseNeoPixelPattern : public NeoPixelPattern {

public:

    static const direction_t FORWARD = 1;
    static const direction_t REVERSE = -1;
    
    color_t color1;
    color_t color2;
    millis_t interval;
    direction_t direction;
    int16_t index;
    
    ChaseNeoPixelPattern(color_t _color1, color_t _color2, millis_t _interval, direction_t _direction = FORWARD) :
        NeoPixelPattern(),
        color1(_color1),
        color2(_color2),
        interval(_interval),
        direction(_direction),
        index(0) {}

    void setup(color_t _color1, color_t _color2, millis_t _interval, direction_t _direction = FORWARD) {
        color1 = _color1;
        color2 = _color2;
        interval = _interval;
        direction = _direction;
        reset();
    }
    
    virtual void reset() {
        index = 0;
    }
    
    virtual void update() {
        for (int i = 0; i < controller->numPixels(); i++) {
            controller->setPixelColor(i, ((i + index) % 3 == 0) ? color1 : color2);
        }
        
        index += direction;
        if (index >= controller->numPixels()) {
            index = 0;
            onLoop();
        } else if (index <= 0) {
            index = controller->numPixels() - 1;
            onLoop();
        }
    }
    
};

#endif
