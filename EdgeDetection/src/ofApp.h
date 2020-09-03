#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void initScene();
	void initFbo();



	//Scene
	ofxAssimpModelLoader model;
	ofVboMesh mesh;
	ofShader lightingShader;
	ofShader edgeShader;
	GLuint lightPass, edgeDetectionPass;
	ofEasyCam cam;

	ofxPanel gui;
	ofParameter<ofVec3f> lightPosition;
	ofParameter<ofVec3f> lightIntensity;
	ofParameter<ofVec3f> Ka;
	ofParameter<ofVec3f> Kd;
	ofParameter<ofVec3f> Ks;
	ofParameter<float> shininess;
	ofParameter<float> EdgeThreshold;

	ofFbo fbo;
	ofFboSettings fboSettings;
	ofMesh quad;
};