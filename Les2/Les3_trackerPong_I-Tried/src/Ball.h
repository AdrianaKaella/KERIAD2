
#pragma once


#include "ofMain.h"

#define BALL_RADIUS 50

class Ball {
        ofPoint position;
        ofVec2f speed;

    public:
        void reset();

        bool update(/*int mouseY*/);

        void draw();
};

