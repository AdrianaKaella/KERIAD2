#pragma once

#include "ofxOpenCv.h"
#include "ofMain.h"

#define HUE_MARGIN 5

static const int GRABBER_HEIGHT = 240;
static const int GRABBER_WIDTH = 320;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		
		ofVideoGrabber grabber;

		ofxCvColorImage rgbImage;

		ofxCvColorImage hsvImage;

		ofxCvGrayscaleImage hue;
		ofxCvGrayscaleImage saturation;
		ofxCvGrayscaleImage value;

		ofxCvGrayscaleImage filtered;

		ofxCvContourFinder contours;

		int selectedHue;
		int selectedHue2;
};
