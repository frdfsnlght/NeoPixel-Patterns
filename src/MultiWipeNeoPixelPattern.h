
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
    
    color_t* colors;
    uint8_t numColors;
    uint8_t mode;
    int16_t index;
    uint8_t color;
    
    MultiWipeNeoPixelPattern(uint8_t numColors) : colors(NULL) {
        updateNumColors(numColors);
    }
    
    ~MultiWipeNeoPixelPattern() {
        if (colors) free(colors);
    }

    void setColor(uint8_t n, color_t color) {
        if (n >= numColors) return;
        colors[n] = color;
    }
    
    void setup(unsigned long _interval, uint8_t _mode = FORWARD) {
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
    
private:

    void updateNumColors(uint8_t n) {
        if (colors) free(colors);
        uint16_t numBytes = n * sizeof(color_t);
        if ((colors = (color_t *)malloc(numBytes))) {
            memset(colors, 0, numBytes);
            numColors = n;
        } else {
            numColors = 0;
        }
    }
    
};

#endif
