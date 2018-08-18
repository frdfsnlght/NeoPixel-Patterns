
#ifndef ChaseNeoPixelPattern_h
#define ChaseNeoPixelPattern_h

#include "NeoPixelPattern.h"

class ChaseNeoPixelPattern : public NeoPixelPattern {

public:

    static const int8_t FORWARD = 0;
    static const int8_t REVERSE = 1;
    
    color_t color1;
    color_t color2;
    int8_t direction;
    int16_t index;
    
    ChaseNeoPixelPattern() {}

    void setup(color_t _color1, color_t _color2, unsigned long _interval, int8_t _direction = FORWARD) {
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
        NeoPixelPattern::update();
        
        for (int i = 0; i < controller->segmentLength(segment); i++) {
            controller->setPixelColor(i, ((i + index) % 3 == 0) ? color1 : color2, segment);
        }
        
        if (direction == FORWARD) {
            index++;
            if (index >= controller->segmentLength(segment)) {
                index = 0;
                looped = true;
            }
        } else {
            index--;
            if (index <= 0) {
                index = controller->segmentLength(segment) - 1;
                looped = true;
            }
        }
    }
    
};

#endif
