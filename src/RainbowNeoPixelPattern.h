
#ifndef RainbowNeoPixelPattern_h
#define RainbowNeoPixelPattern_h

#include "NeoPixelPattern.h"

class RainbowNeoPixelPattern : public NeoPixelPattern {

public:

    static const int8_t FORWARD = 0;
    static const int8_t REVERSE = 1;
    
    int8_t direction;
    int16_t index;
    
    RainbowNeoPixelPattern() {}

    void setup(unsigned long _interval, int8_t _direction = FORWARD) {
        interval = _interval;
        direction = _direction;
        reset();
    }
    
    virtual void reset() {
        index = 0;
    }
    
    virtual void update() {
        NeoPixelPattern::update();
        for (int i = 0; i < controller->segmentLength(segment); i++) {
            controller->setPixelColor(i, NeoPixelController::Wheel(((i * 256 / controller->segmentLength(segment)) + index) & 255), segment);
        }
        
        if (direction == FORWARD) {
            index++;
            if (index >= 255) {
                index = 0;
                looped = true;
            }
        } else {
            index--;
            if (index <= 0) {
                index = 254;
                looped = true;
            }
        }
    }
    
};

#endif
