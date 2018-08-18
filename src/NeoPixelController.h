
#ifndef NeoPixelController_h
#define NeoPixelController_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "NeoPixelPattern.h"
#include "Colors.h"

class NeoPixelPattern;

typedef struct {
    uint16_t basePixel;
    uint16_t length;
    NeoPixelPattern* pattern;
} segment_t;

class NeoPixelController : public Adafruit_NeoPixel {
    
public:

    NeoPixelController(uint16_t numPixels, uint8_t numSegments, uint8_t pin, uint8_t type = NEO_GRB + NEO_KHZ800);
    ~NeoPixelController();

    void updateSegments(uint8_t n);
    void setupSegment(uint8_t segment, uint16_t basePixel, uint16_t length);
    
    inline bool isSegmentActive(uint8_t segment) {
        return segments[segment].pattern != NULL;
    }
    
    bool isPatternActive(NeoPixelPattern& pattern, uint8_t segment) {
        return segments[segment].pattern == &pattern;
    }
    
    NeoPixelPattern* getPattern(uint8_t segment) {
        return segments[segment].pattern;
    }
    
    void setPattern(NeoPixelPattern* pattern, uint8_t segment) {
        segments[segment].pattern = pattern;
    }
    
    void play(NeoPixelPattern& pattern, uint8_t segment);
    void pause(uint8_t segment);
    void resume(uint8_t segment);
    void stop(uint8_t segment);
    
    void update();
    void stop();
    
    void setSegmentColor(color_t color, uint8_t segment);
    void setPixelColor(uint16_t pixel, color_t color, uint8_t segment);
    color_t getPixelColor(uint16_t pixel, uint8_t segment);
    
    inline uint16_t segmentBasePixel(uint8_t segment) {
        return segments[segment].basePixel;
    }
    
    inline uint16_t segmentLength(uint8_t segment) {
        return segments[segment].length;
    }
        
    static color_t Wheel(byte wheelPos) {
        wheelPos = 255 - wheelPos;
        if (wheelPos < 85) {
            return Color(255 - wheelPos * 3, 0, wheelPos * 3);
        } else if (wheelPos < 170) {
            wheelPos -= 85;
            return Color(0, wheelPos * 3, 255 - wheelPos * 3);
        } else {
            wheelPos -= 170;
            return Color(wheelPos * 3, 255 - wheelPos * 3, 0);
        }
    }

protected:

    uint8_t numSegments;
    uint16_t numBytes;
    segment_t* segments;
    
};

#endif

