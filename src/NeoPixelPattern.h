
#ifndef NeoPixelPattern_h
#define NeoPixelPattern_h

#include "NeoPixel-Patterns.h"

class NeoPixelController;

class NeoPixelPattern {

public:

    static const direction_t FORWARD = 1;
    static const direction_t REVERSE = -1;
    
    static const state_t STOP = 0;
    static const state_t PLAY = 1;
    static const state_t PAUSE = 2;
    static const state_t COMPLETE = 3;

    NeoPixelController* controller;
    state_t state;
    millis_t lastUpdate;
    millis_t interval;
    
    void (*onLoopCallback)(NeoPixelPattern*);
    void (*onCompleteCallback)(NeoPixelPattern*);
    
    NeoPixelPattern() :
        controller(NULL),
        state(STOP),
        lastUpdate(0),
        interval(0),
        onLoopCallback(NULL),
        onCompleteCallback(NULL) {}
    
    void setOnLoopCallback(void (*callback)(NeoPixelPattern*)) {
        onLoopCallback = callback;
    }
    
    void setOnCompleteCallback(void (*callback)(NeoPixelPattern*)) {
        onCompleteCallback = callback;
    }
    
    bool isComplete() {
        return state == COMPLETE;
    }
    
    bool needsUpdate() {
        return millis() - lastUpdate > interval;
    }

    void play(NeoPixelController* ctrl) {
        controller = ctrl;
        lastUpdate = 0;
        state = PLAY;
        reset();
    }
    
    virtual void reset() {}
    virtual void update() {}
    virtual void pause() {}
    virtual void resume() {}
    virtual void stop() {}
    
    virtual void increment() {}
    
    virtual void onLoop() {
        if (onLoopCallback != NULL) {
            onLoopCallback(this);
        }
    }
    
    virtual void onComplete() {
        if (onCompleteCallback != NULL) {
            onCompleteCallback(this);
        }
    }
    
    /*
    void afterUpdate() {
        lastUpdate = millis();
        if (isComplete()) {
            onComplete();
        }
        if (! isComplete()) {
            increment();
        }
    }
    */
    
    
    /*
    // Increment the Index and reset at the end
    void Increment()
    {
        Index += Direction;
        if (Index >= TotalSteps)
        {
            Index = 0;
            OnComplete();
        }
        else if (Index <= 0)
        {
            Index = TotalSteps - 1;
            OnComplete();
        }
    }
    
    // Reverse pattern direction
    void Reverse()
    {
        Direction *= -1;
        Index = (Direction == FORWARD) ? 0 : TotalSteps - 1;
    }

    NeoPatterns& Pixels;        // Which pixels to manipulate
    millis_t Interval;          // Milliseconds between updates
    millis_t LastUpdate;        // last update of position
    color_t Color1, Color2;     // What color(s) to use
    uint16_t TotalSteps;        // Total number of steps in the pattern
    uint16_t Index;             // Current step within the pattern
    direction_t Direction;      // Direction to run the pattern
    */
    
};


#endif
