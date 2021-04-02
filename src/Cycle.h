#ifndef CYCLE_H
#define CYCLE_H

#include "ofMain.h"

class Cycle {
  public:
    void setup();
    void draw();
    void resetStarsEvent();

    ofParameterGroup params;
    ofParameter<float> rotation;
    ofParameter<void> resetStars;

    ofColor day;
    ofColor night;
    ofColor sun;
    ofColor moon;
    ofColor land;
    ofColor land_n;

    array<ofVec2f, 100> star_pos;
};

#endif

