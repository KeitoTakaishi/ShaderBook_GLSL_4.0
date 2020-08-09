#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#define LIGHT_NUM 7
class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void initScene();
	void initLight();
	void initGUI();
	void createUBO();


	ofxAssimpModelLoader model;
	ofVboMesh mesh;
	ofPlanePrimitive plane;
	ofShader shader;
	ofEasyCam cam;


	//shader_uniforms==========
	typedef struct  {
		ofVec3f position;
		ofVec3f intensity;
	} LightInfo;
	
	LightInfo lightInfo[LIGHT_NUM];

	//ubo
	GLuint programHandle;
	GLint blockIndex;
	GLint blockSize;
	GLuint uboHandle;
	GLubyte* blockBuffer;

	ofVec4f Ka, Kd, Ks;
	float shininess;
	//Gui
	ofxPanel gui;
	ofParameter<ofVec3f> _Ka;
	ofParameter<ofVec3f> _Kd;
	ofParameter<ofVec3f> _Ks;
	ofParameter<float> _shininess;
	ofParameter<ofColor> startColor, endColor;
};