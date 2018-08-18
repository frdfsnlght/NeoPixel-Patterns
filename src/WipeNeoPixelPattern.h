
#ifndef WipeNeoPixelPattern_h
#define WipeNeoPixelPattern_h

#include "NeoPixelPattern.h"

class WipeNeoPixelPattern : public NeoPixelPattern {

public:

    static const uint8_t FORWARD = 0;
    static const uint8_t REVERSE = 1;
    static const uint8_t ENDS_IN = 2;
    static const uint8_t CENTER_OUT = 3;
    
    color_t color;
    uint8_t mode;
    int16_t index;
    
    WipeNeoPixelPattern() {}

    void setup(color_t _color, unsigned long _interval, uint8_t _mode = FORWARD) {
        color = _color;
        interval = _interval;
        mode = _mode;
    }
    
    virtual void reset() {
        index = 0;
    }
    
    virtual void update() {
        NeoPixelPattern::update();
        switch (mode) {
            case FORWARD:
                controller->setPixelColor(index++, color, segment);
                complete = index >= controller->segmentLength(segment);
                break;
            case REVERSE:
                controller->setPixelColor(controller->segmentLength(segment) - ++index, color, segment);
                complete = index > controller->segmentLength(segment);
                break;
            case ENDS_IN:
                controller->setPixelColor(index++, color, segment);
                controller->setPixelColor(controller->segmentLength(segment) - index, color, segment);
                complete = index > controller->segmentLength(segment) / 2;
                break;
            case CENTER_OUT:
                controller->setPixelColor((controller->segmentLength(segment) / 2) - index, color, segment);
                controller->setPixelColor((controller->segmentLength(segment) / 2) + index++, color, segment);
                complete = index > controller->segmentLength(segment) / 2;
                break;
        }
    }
    
};

#endif
