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
		ofParameter<ofVec3f> _Ka;
		ofParameter<ofVec3f> _Kd;
		ofParameter<ofVec3f> _Ks;
		ofParameter<float> _shininess;

	
		
};
