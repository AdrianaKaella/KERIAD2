#include "Ball.h"
#include "ofApp.h"

void Ball::reset() {
    position = ofPoint(ofGetWidth() / 4, ofGetHeight() / 2);
    speed = ofVec2f(ofRandom(1, 3) * 2 + 1, ofRandom(-1, 1) * 3 + 2);
}

bool Ball::update(/*int mouseY*/) {
    position += speed;

    if (position.y > ofGetHeight() - BALL_RADIUS || position.y < BALL_RADIUS) {
        speed.y = -speed.y;
    }

    if (position.x > ofGetWidth() - BALL_RADIUS - ofApp::PADDLE_WIDTH) {
        if (position.y >= /*mouseY*/ contours.blobs[i].centroid.y - ofApp::PADDLE_HEIGHT / 2 && position.y <= mouseY + ofApp::PADDLE_HEIGHT / 2) {
            speed.x = -speed.x;
        } else {
            reset();
            return true;
        }
    } else if (position.x < BALL_RADIUS) {
        speed.x = -speed.x;
    }
    return false;
}

void Ball::draw() {
    ofSetColor(ofColor::green);
    ofDrawCircle(position, BALL_RADIUS);
}
