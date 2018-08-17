
#ifndef NeoPixelPattern_h
#define NeoPixelPattern_h

#include <Arduino.h>

#include "NeoPixelController.h"

class NeoPixelController;

class NeoPixelPattern {

public:

    static const uint8_t STOP = 0;
    static const uint8_t PLAY = 1;
    static const uint8_t PAUSE = 2;

    NeoPixelPattern() :
        controller(NULL),
        segment(0),
        state(STOP),
        lastUpdate(0),
        interval(0),
        looped(false),
        complete(false),
        onLoopCallback(NULL),
        onCompleteCallback(NULL) {}
    
    void setOnLoopCallback(void (*callback)(NeoPixelPattern*)) {
        onLoopCallback = callback;
    }
    
    void setOnCompleteCallback(void (*callback)(NeoPixelPattern*)) {
        onCompleteCallback = callback;
    }
    
    inline bool isPlaying() {
        return state == PLAY;
    }
    
    inline bool isPaused() {
        return state == PAUSE;
    }
    
    inline bool isStopped() {
        return state == STOP;
    }
    
    inline bool isLooped() {
        return looped;
    }
    
    inline bool isComplete() {
        return complete;
    }
    
    inline bool needsUpdate() {
        return (! complete) && (millis() - lastUpdate > interval);
    }

    void play(NeoPixelController* ctrl, uint8_t segment) {
        controller = ctrl;
        segment = segment;
        lastUpdate = 0;
        state = PLAY;
        looped = complete = false;
        reset();
    }
    
    virtual void reset() {}
    virtual void update() {}
    virtual void pause() {}
    virtual void resume() {}
    virtual void stop() {}
    
    virtual void onLoop() {
        if (onLoopCallback != NULL) {
            onLoopCallback(this);
        }
        looped = false;
    }
    
    virtual void onComplete() {
        if (onCompleteCallback != NULL) {
            onCompleteCallback(this);
        }
    }
    
protected:
    NeoPixelController* controller;
    uint8_t segment;
    uint8_t state;
    unsigned long lastUpdate;
    unsigned long interval;
    bool looped;
    bool complete;
    void (*onLoopCallback)(NeoPixelPattern*);
    void (*onCompleteCallback)(NeoPixelPattern*);
    
};


#endif
