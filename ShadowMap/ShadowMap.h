#pragma once
#include "ofMain.h"

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	void renderDepthBegin();
	void renderDepthEnd();

	void camBegin();
	void camEnd();

	void drawDepthFbo();
	

	void moveLight(float radius, float speed);
	void drawLight();



	ofFbo depthFbo;
	ofEasyCam lightCam;
	ofVec3f lightPos;
	ofVec3f camUp, camTarget;
	ofMatrix4x4 viewMatrix;
	ofMatrix4x4 projMatrix;
	ofMatrix4x4 biasMatrix;
	ofMatrix4x4 shadowMatrix;
};

