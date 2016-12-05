#pragma once

#include "ofxOpenCv.h"
#include "ofMain.h"
#include "Ball.h"

#define HUE_MARGIN 5

static const int GRABBER_HEIGHT = 240;
static const int GRABBER_WIDTH = 320;


class ofApp : public ofBaseApp {

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void mousePressed(int x, int y, int button);

        static const int PADDLE_WIDTH = 20;
        static const int PADDLE_HEIGHT = 150;

		ofVideoGrabber grabber;

		ofxCvColorImage rgbImage;

		ofxCvColorImage hsvImage;

		ofxCvGrayscaleImage hue;
		ofxCvGrayscaleImage saturation;
		ofxCvGrayscaleImage value;

		ofxCvGrayscaleImage filtered;

		ofxCvContourFinder contours;

		int centroidY;

		int selectedHue;

		bool showHSVComponents = true;
		bool showFilter = true;
		bool showContours = true;
		bool showVideo = true;

    private:
        Ball ball;
        int missedCount;
};
