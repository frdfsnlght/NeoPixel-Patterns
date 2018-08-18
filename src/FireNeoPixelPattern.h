
/*
 Adapated from https://github.com/FastLED/FastLED/blob/master/examples/Fire2012/Fire2012.ino
*/
 
// Cooling 55
// Sparking 120

#ifndef FireNeoPixelPattern_h
#define FireNeoPixelPattern_h

#include "NeoPixelPattern.h"

class FireNeoPixelPattern : public NeoPixelPattern {

public:

    static const uint8_t FORWARD = 0;
    static const uint8_t REVERSE = 1;
    
    uint16_t cooling;
    uint16_t sparking;
    uint8_t direction;
    byte* heat;
    uint16_t numBytes;
    
    FireNeoPixelPattern() : heat(NULL) {}
    ~FireNeoPixelPattern() {
        if (heat) free(heat);
    }        

    void setup(uint16_t _cooling, uint16_t _sparking, unsigned long _interval, uint8_t _direction) {
        cooling = _cooling;
        sparking = _sparking;
        interval = _interval;
        direction = _direction;
    }
    
    virtual void reset() {
        if (heat) free(heat);
        numBytes = controller->segmentLength(segment);
        if ((heat = (byte *)malloc(numBytes))) {
            memset(heat, 0, numBytes);
        } else {
            numBytes = 0;
        }
    }
    
    virtual void update() {
        NeoPixelPattern::update();

        // Step 1.  Cool down every cell a little
        for (int i = 0; i < numBytes; i++) {
            uint8_t cold = random(((cooling * 10) / numBytes) + 2);
            if (cold >= heat[i]) heat[i] = 0;
            else heat[i] -= cold;
        }
  
        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for (int k = numBytes - 1; k >= 2; k--) {
            heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
        }
    
        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if (random(0, 256) < sparking) {
            //int y = random(7);
            uint16_t y = random(numBytes >> 2);
            uint8_t hot = random(160, 255);
            if (heat[y] + hot < heat[y]) heat[y] = 0xff;
            else heat[y] += hot;
        }

        // Step 4.  Map from heat cells to LED colors
        for (int j = 0; j < numBytes; j++) {
            color_t color = heatColor(heat[j]);
            uint16_t pixelnumber;
            if (direction) {
                pixelnumber = (numBytes - 1) - j;
            } else {
                pixelnumber = j;
            }
            controller->setPixelColor(pixelnumber, color, segment);
        }
    }
    
    color_t heatColor(uint8_t temp) {

        // Scale 'heat' down from 0-255 to 0-191,
        // which can then be easily divided into three
        // equal 'thirds' of 64 units each.
        uint8_t t192 = (temp == 0) ? 0 : (((int)temp * (int)192) >> 8) + 1;

        // calculate a value that ramps up from
        // zero to 255 in each 'third' of the scale.
        uint8_t heatramp = t192 & 0x3F; // 0..63
        heatramp <<= 2; // scale up to 0..252

        // now figure out which third of the spectrum we're in:
        if (t192 & 0x80) {
            // we're in the hottest third
            return COLOR(255, 255, heatramp);
        } else if (t192 & 0x40) {
            // we're in the middle third
            return COLOR(255, heatramp, 0);
        } else {
            // we're in the coolest third
            return COLOR(heatramp, 0, 0);
        }
    }
    
};

#endif
