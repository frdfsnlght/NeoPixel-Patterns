
#ifndef ScanNeoPixelPattern_h
#define ScanNeoPixelPattern_h

#include "NeoPixelPattern.h"

class ScanNeoPixelPattern : public NeoPixelPattern {

public:

    color_t color;
    int16_t index;
    int16_t direction;
    
    ScanNeoPixelPattern() {}

    void setup(color_t _color, unsigned long _interval) {
        color = _color;
        interval = _interval;
        reset();
    }
    
    virtual void reset() {
        index = 0;
        direction = 1;
    }
    
    virtual void update() {
        for (int i = 0; i < controller->numSegmentPixels(segment); i++) {
            if (i == index) {
                controller->setPixelColor(i, color, segment);
            } else {
                controller->setPixelColor(i, DIMCOLOR(controller->getPixelColor(i, segment)), segment);
            }
        }
        
        index += direction;
        if (index >= controller->numSegmentPixels(segment)) {
            direction = -direction;
            index = controller->numSegmentPixels(segment) - 2;
        } else if (index < 0) {
            direction = -direction;
            index = 1;
            looped = true;
        }
    }
    
};

#endif
