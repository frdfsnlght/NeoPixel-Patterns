
#ifndef RainbowNeoPixelPattern_h
#define RainbowNeoPixelPattern_h

#include "NeoPixel-Patterns.h"

class RainbowNeoPixelPattern : public NeoPixelPattern {

public:

    static const direction_t FORWARD = 1;
    static const direction_t REVERSE = -1;
    
    millis_t interval;
    direction_t direction;
    int16_t index;
    
    RainbowNeoPixelPattern(millis_t _interval, direction_t _direction = FORWARD) :
        NeoPixelPattern(),
        interval(_interval),
        direction(_direction),
        index(0) {}

    void setup(millis_t _interval, direction_t _direction = FORWARD) {
        interval = _interval;
        direction = _direction;
        reset();
    }
    
    virtual void reset() {
        index = 0;
    }
    
    virtual void update() {
        for (int i = 0; i < controller->numPixels(); i++) {
            controller->setPixelColor(i, NeoPixelController::Wheel(((i * 256 / controller->numPixels()) + index) & 255));
        }
        
        index += direction;
        if (index >= 255) {
            index = 0;
            onLoop();
        } else if (index <= 0) {
            index = 254;
            onLoop();
        }
    }
    
};

#endif
