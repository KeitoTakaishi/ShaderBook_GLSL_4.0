#pragma once

#include "ofMain.h"
#define NUM 10
class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	ofShader shader;
	ofEasyCam cam;
	ofBoxPrimitive box[NUM];
	ofVec3f pos[NUM];
	GLuint  redPass, greenPass, bluePass;
};