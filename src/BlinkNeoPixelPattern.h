
#ifndef BlinkNeoPixelPattern_h
#define BlinkNeoPixelPattern_h

#include "NeoPixelPattern.h"

class BlinkNeoPixelPattern : public NeoPixelPattern {

public:

    color_t color1;
    color_t color2;
    unsigned long interval1;
    unsigned long interval2;
    bool showColor1;
    
    BlinkNeoPixelPattern() {}

    void setup(color_t _color1, color_t _color2, unsigned long _interval1, unsigned long _interval2) {
        color1 = _color1;
        color2 = _color2;
        interval1 = _interval1;
        interval2 = _interval2;
    }
    
    virtual void reset() {
        showColor1 = true;
        interval = 0;
    }
    
    virtual void update() {
        if (showColor1) {
            controller->setSegmentColor(color1, segment);
            looped = interval > 0;
            interval = interval1;
            showColor1 = false;
        } else {
            controller->setSegmentColor(color2, segment);
            interval = interval2;
            showColor1 = true;
        }
    }
    
};

#endif
