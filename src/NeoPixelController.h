
#ifndef NeoPixelController_h
#define NeoPixelController_h

#include "NeoPixel-Patterns.h"
#include <Adafruit_NeoPixel.h>

class NeoPixelPattern;

class NeoPixelController : public Adafruit_NeoPixel {
    
public:

    static const state_t STOP = 0;
    static const state_t PLAY = 1;
    static const state_t PAUSE = 2;

    NeoPixelPattern* activePattern;
    state_t state;
    
    NeoPixelController(uint16_t pixels, uint8_t pin, uint8_t type = NEO_GRB + NEO_KHZ800) :
        Adafruit_NeoPixel(pixels, pin, type),
        activePattern(NULL),
        state(STOP) {}

    bool isActive() {
        return activePattern != NULL;
    }

    bool isActive(const NeoPixelPattern& pattern) const {
        return activePattern == &pattern;
    }

    bool isPlaying() {
        return state == PLAY;
    }
    
    bool isPaused() {
        return state == PAUSE;
    }
    
    void play(NeoPixelPattern& pattern);
    void pause();
    void resume();
    void stop();
    void update();

    void setColor(color_t color) {
        for (int i = 0; i < numPixels(); ++i) {
            setPixelColor(i, color);
        }
        show();
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
    
};

#endif

