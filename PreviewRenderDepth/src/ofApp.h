#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define WALLNUM 3
#define SPHERE_NUN 30
#define BOX_NUN 30

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	void preload();
	void initGUI();
	void initBaseScene();
	void drawWall(ofEasyCam& cam, ofShader& shader);
	void drawSceneElements(ofEasyCam& cam, ofShader& shader);

	void setLightParames();
	void previewLight();

	void initFbo();


	ofEasyCam cam;

	//shaders
	ofShader debugShader;
	ofShader previewShader;
	ofShader shadowShader;
	//fbo
	ofFbo renderFbo;

	//Light
	ofSpherePrimitive lightObj;
	ofEasyCam lightProjector;
	ofMatrix4x4 biasMatrix;
	ofMatrix4x4 lightViewMatrix;
	ofMatrix4x4 lightProjMatrix;



	//BaseSceneElemenet
	ofPlanePrimitive wall[WALLNUM];
	float wallSize = 1500;
	ofSpherePrimitive spheres[SPHERE_NUN];
	ofBoxPrimitive boxes[BOX_NUN];
	ofVec3f spherePos[SPHERE_NUN];
	float sphereRadius[SPHERE_NUN];
	ofVec3f boxPos[BOX_NUN];
	ofVec3f boxScale[BOX_NUN];


	//Gui
	ofxPanel lightGui;
	ofParameter<ofVec3f> lightPos;
	ofParameter<ofVec2f> lightProjClip;
	ofParameter<float> lightProjFov;

	//Quad(FinaleRender)
	ofMesh quad;



};
