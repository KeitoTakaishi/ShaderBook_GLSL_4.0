#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void initGui();
	void createTexture();
	void setupProjector();


	ofEasyCam cam;
	ofEasyCam projctor;
	ofShader shader;
	ofMatrix4x4 bias;

	ofImage img;
	ofTexture tex;
	ofBoxPrimitive box;
	ofSpherePrimitive sphere;
	GLuint texID;
	GLuint loc;

	//Gui
	ofxPanel projectorGui;
	ofParameter<ofVec2f> projClip;
	ofParameter<float> projFov;
	ofParameter<ofVec3f> projPos;


};
