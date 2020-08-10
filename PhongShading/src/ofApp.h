#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void initScene();
		void initGUI();


		//Scene
		ofxAssimpModelLoader model;
		ofVboMesh mesh;
		ofPlanePrimitive plane;
		ofShader shader;
		ofEasyCam cam;


		//gui
		ofxPanel gui;
		ofParameter<ofVec3f> lightPosition;
		ofParameter<ofVec3f> lightIntensity;
		ofParameter<ofVec3f> Ka;
		ofParameter<ofVec3f> Kd;
		ofParameter<ofVec3f> Ks;
		ofParameter<float> shininess;
		ofxToggle optimize;

	
		
};
