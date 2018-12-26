
#ifndef MultiWipeNeoPixelPattern_h
#define MultiWipeNeoPixelPattern_h

#include "NeoPixelPattern.h"

class MultiWipeNeoPixelPattern : public NeoPixelPattern {

public:

    static const uint8_t FORWARD = 0;
    static const uint8_t REVERSE = 1;
    static const uint8_t ENDS_IN = 2;
    static const uint8_t CENTER_OUT = 3;
    static const uint8_t REPEAT = 4;
    
    static const uint8_t MAX_COLORS = 4;
    
    color_t colors[MAX_COLORS];
    uint8_t numColors;
    uint8_t mode;
    int16_t index;
    uint8_t color;
    
    MultiWipeNeoPixelPattern() {}
    
    void setColor(uint8_t n, color_t color) {
        if (n >= numColors) return;
        colors[n] = color;
    }
    
    void setup(uint8_t _numColors, unsigned long _interval, uint8_t _mode = FORWARD) {
        numColors = (_numColors > MAX_COLORS) ? MAX_COLORS : _numColors;
        interval = _interval;
        mode = _mode;
    }
    
    virtual void reset() {
        numColors = 0;
        index = 0;
        color = 0;
    }
    
    virtual void update() {
        bool colorComplete = false;
        NeoPixelPattern::update();
        switch (mode & ~REPEAT) {
            case FORWARD:
                controller->setPixelColor(index++, colors[color], segment);
                colorComplete = index >= controller->segmentLength(segment);
                break;
            case REVERSE:
                controller->setPixelColor(controller->segmentLength(segment) - ++index, colors[color], segment);
                colorComplete = index > controller->segmentLength(segment);
                break;
            case ENDS_IN:
                controller->setPixelColor(index++, colors[color], segment);
                controller->setPixelColor(controller->segmentLength(segment) - index, colors[color], segment);
                colorComplete = index > controller->segmentLength(segment) / 2;
                break;
            case CENTER_OUT:
                controller->setPixelColor((controller->segmentLength(segment) / 2) - index, colors[color], segment);
                controller->setPixelColor((controller->segmentLength(segment) / 2) + index++, colors[color], segment);
                colorComplete = index > controller->segmentLength(segment) / 2;
                break;
        }
        if (colorComplete) {
            color++;
            index = 0;
            if (color >= numColors) {
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
