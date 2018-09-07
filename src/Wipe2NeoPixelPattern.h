
#ifndef Wipe2NeoPixelPattern_h
#define Wipe2NeoPixelPattern_h

#include "NeoPixelPattern.h"

class Wipe2NeoPixelPattern : public NeoPixelPattern {

public:

    static const uint8_t FORWARD = 0;
    static const uint8_t REVERSE = 1;
    static const uint8_t ENDS_IN = 2;
    static const uint8_t CENTER_OUT = 3;
    static const uint8_t REPEAT = 4;
    
    color_t color1;
    color_t color2;
    uint8_t mode;
    int16_t index;
    byte color;
    
    Wipe2NeoPixelPattern() {}

    void setup(color_t _color1, color_t _color2, unsigned long _interval, uint8_t _mode = FORWARD) {
        color1 = _color1;
        color2 = _color2;
        interval = _interval;
        mode = _mode;
    }
    
    virtual void reset() {
        index = 0;
        color = 0;
    }
    
    virtual void update() {
        bool colorComplete = false;
        NeoPixelPattern::update();
        switch (mode & ~REPEAT) {
            case FORWARD:
                controller->setPixelColor(index++, color ? color2 : color1, segment);
                colorComplete = index >= controller->segmentLength(segment);
                break;
            case REVERSE:
                controller->setPixelColor(controller->segmentLength(segment) - ++index, color ? color2 : color1, segment);
                colorComplete = index > controller->segmentLength(segment);
                break;
            case ENDS_IN:
                controller->setPixelColor(index++, color, segment);
                controller->setPixelColor(controller->segmentLength(segment) - index, color ? color2 : color1, segment);
                colorComplete = index > controller->segmentLength(segment) / 2;
                break;
            case CENTER_OUT:
                controller->setPixelColor((controller->segmentLength(segment) / 2) - index, color ? color2 : color1, segment);
                controller->setPixelColor((controller->segmentLength(segment) / 2) + index++, color ? color2 : color1, segment);
                colorComplete = index > controller->segmentLength(segment) / 2;
                break;
        }
        if (colorComplete) {
            color++;
            index = 0;
            if (color == 2) {
                if (mode & REPEAT) {
                    looped = true;
                    color = 0;
                } else {
                    complete = true;
                }
            }
        }
    }
    
};

#endif
