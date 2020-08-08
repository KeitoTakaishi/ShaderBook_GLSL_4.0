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



	ofxAssimpModelLoader model;
	ofVboMesh mesh;
	ofShader shader;
	ofEasyCam cam;

	//ubo
	GLint blockIndex_LightInfo;
	GLint blockSize_LightInfo;
	GLuint uboHandle_LightInfo;
	GLint blockIndex_MaterialInfo;
	GLint blockSize_MaterialInfo;
	GLuint uboHandle_MaterialInfo;
	GLubyte* blockBuffer_light;
	GLubyte* blockBuffer_material;

	ofVec4f _La, _Ld, _Ls;
	ofVec4f _Ka, _Kd, _Ks;

	//Gui
	ofxPanel gui;
	ofParameter<ofVec3f> lightPos;
	ofParameter<ofVec3f> La;
	ofParameter<ofVec3f> Ld;
	ofParameter<ofVec3f> Ls;

	ofParameter<ofVec3f> Ka;
	ofParameter<ofVec3f> Kd;
	ofParameter<ofVec3f> Ks;
	ofParameter<float> shininess;
	ofxToggle debug;
};