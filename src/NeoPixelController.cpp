
#include "NeoPixelController.h"
#include "NeoPixelPattern.h"

void NeoPixelController::play(NeoPixelPattern& pattern) {
    if (activePattern != NULL) {
        stop();
    }
    activePattern = &pattern;
    state = PLAY;
    activePattern->play(this);
}

void NeoPixelController::pause() {
    if (isPlaying()) {
        state = PAUSE;
        activePattern->pause();
    }
}

void NeoPixelController::resume() {
    if (isPaused()) {
        state = PLAY;
        activePattern->resume();
    }
}
    
void NeoPixelController::stop() {
    if (isPlaying() || isPaused()) {
        state = STOP;
        activePattern->stop();
        activePattern = NULL;
        clear();
        show();
    }
}

void NeoPixelController::update() {
    if (isActive() && isPlaying()) {
        if (activePattern->needsUpdate()) {
            activePattern->update();
            show();
            if (activePattern->isComplete()) {
                state = STOP;
                activePattern = NULL;
//            } else {
//                activePattern->afterUpdate();
            }
        }
    }
}

