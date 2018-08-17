
#include "NeoPixelController.h"
#include "NeoPixelPattern.h"

NeoPixelController::NeoPixelController(uint16_t numPixels, uint8_t numSegments, uint8_t pin, uint8_t type) :
    Adafruit_NeoPixel(numPixels, pin, type),
    numSegments(0),
    segments(NULL) {
    
    updateSegments(numSegments);
}

NeoPixelController::~NeoPixelController() {
    if (segments) free(segments);
}

void NeoPixelController::updateSegments(uint8_t n) {
    if (segments) free(segments);
    numBytes = n * sizeof(segment_t);
    if ((segments = (segment_t *)malloc(numBytes))) {
        memset(segments, 0, numBytes);
        numSegments = n;
    } else {
        numSegments = numBytes = 0;
    }
}

void NeoPixelController::setupSegment(uint8_t segment, uint16_t basePixel, uint16_t length) {
    segments[segment].basePixel = basePixel;
    segments[segment].length = length;
}

void NeoPixelController::play(NeoPixelPattern& pattern, uint8_t segment) {
    if (segments[segment].pattern != NULL) {
        stop(segment);
    }
    segments[segment].pattern = &pattern;
    segments[segment].pattern ->play(this, segment);
}

void NeoPixelController::pause(uint8_t segment) {
    if (segments[segment].pattern != NULL) {
        if (segments[segment].pattern->isPlaying()) {
            segments[segment].pattern->pause();
        }
    }
}

void NeoPixelController::resume(uint8_t segment) {
    if (segments[segment].pattern != NULL) {
        if (segments[segment].pattern->isPaused()) {
            segments[segment].pattern->resume();
        }
    }
}
    
void NeoPixelController::stop(uint8_t segment) {
    if (segments[segment].pattern != NULL) {
        if (segments[segment].pattern->isPlaying() || segments[segment].pattern->isPaused()) {
            segments[segment].pattern->stop();
        }
        segments[segment].pattern = NULL;
    }
}

void NeoPixelController::update() {
    bool needShow = false;
    for (int i = 0; i < numSegments; i++) {
        if (segments[i].pattern != NULL) {
            if (segments[i].pattern->needsUpdate()) {
                segments[i].pattern->update();
                needShow = true;
            }
            if (segments[i].pattern->isLooped()) {
                segments[i].pattern->onLoop();
            }
            if (segments[i].pattern->isComplete()) {
                segments[i].pattern->onComplete();
            }
        }
    }
    if (needShow) {
        show();
    }
}    

void NeoPixelController::stop() {
    for (int i = 0; i < numSegments; i++) {
        stop(i);
    }
}

void NeoPixelController::setSegmentColor(color_t color, uint8_t segment) {
    for (int i = 0; i < segments[segment].length; i++) {
        Adafruit_NeoPixel::setPixelColor(segments[segment].basePixel + i, color);
    }
    show();
}

void NeoPixelController::setPixelColor(uint16_t pixel, color_t color, uint8_t segment) {
    Adafruit_NeoPixel::setPixelColor(pixel + segments[segment].basePixel, color);
}

color_t NeoPixelController::getPixelColor(uint16_t pixel, uint8_t segment) {
    return Adafruit_NeoPixel::getPixelColor(pixel + segments[segment].basePixel);
}



