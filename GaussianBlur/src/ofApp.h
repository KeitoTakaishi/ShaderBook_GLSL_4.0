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
		void initFbo();
		void calcBlurParam();
		float gauss(float x, float sigma2);

		
		ofxAssimpModelLoader model;
		ofVboMesh mesh;
		

		//shaders
		ofShader lightingShader;
		ofShader blurShader;
		GLuint lightPass, FirstBlurPass, SecondBlurPass;
		ofEasyCam cam;

		//blur parames
		float weights[5];
		float sum;
		

		//utils
		ofxPanel gui;
		ofParameter<ofVec3f> lightPosition;
		ofParameter<ofVec3f> lightIntensity;
		ofParameter<ofVec3f> Ka;
		ofParameter<ofVec3f> Kd;
		ofParameter<ofVec3f> Ks;
		ofParameter<float> shininess;
		ofParameter<float> sigma2;
		

		ofFbo renderFbo, blurFbo;
		ofFboSettings fboSettings;
		ofMesh quad;
};
