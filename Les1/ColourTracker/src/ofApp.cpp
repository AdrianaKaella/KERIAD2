#include "ofApp.h"

void ofApp::setup(){
	grabber.setup(GRABBER_WIDTH, GRABBER_HEIGHT, true);

	rgbImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	hsvImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	hue.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	saturation.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	value.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);

	filtered.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
}


void ofApp::update(){
	grabber.update();
	
	if (grabber.isFrameNew()) {
		rgbImage.setFromPixels(grabber.getPixels().getData(), GRABBER_WIDTH, GRABBER_HEIGHT);
		rgbImage.mirror(false, true);

		hsvImage = rgbImage;
		hsvImage.convertRgbToHsv();

		hsvImage.convertToGrayscalePlanarImages(hue, saturation, value);

		for (int i = 0; i < GRABBER_WIDTH*GRABBER_HEIGHT; i++)
		{
			if (ofInRange(hue.getPixels()[i], selectedHue-HUE_MARGIN, selectedHue+HUE_MARGIN)) {
				filtered.getPixels()[i] = 255;
			}

			else if (ofInRange(hue.getPixels()[i], selectedHue2 - HUE_MARGIN, selectedHue2 + HUE_MARGIN)) {
				filtered.getPixels()[i] = 255;
			}

			else {
				filtered.getPixels()[i] = 0;
			}

		}

		filtered.flagImageChanged();
	}
}


void ofApp::draw(){
	rgbImage.draw(640, 0);

	hsvImage.draw(0, 0); 
	hue.draw(0, 240);
	saturation.draw(320, 240);
	value.draw(640, 240);
	filtered.draw(0, 480);
}


void ofApp::keyPressed(int key){

}


void ofApp::mousePressed(int x, int y, int button){
	if (button == 0) {
		selectedHue = hue.getPixels()[y * GRABBER_WIDTH + x];
		ofLog() << "Selected: " << selectedHue << endl;
	}

	if (button == 2) {
		selectedHue2 = hue.getPixels()[y * GRABBER_WIDTH + x];
		ofLog() << "Selected: " << selectedHue2 << endl;
	}
	
}
