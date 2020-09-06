#pragma once

#include "ofMain.h"
#include "../ShadowMap.h"
#include "../MatrixUtil.h"
#define sphereNum  30
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void render2Fbo(ofShader& shader);
		
		ShadowMap* shadowMap;


		//reneder
		ofEasyCam cam;
		ofVec3f camUp = ofVec3f(0.0, 1.0, 0.0);
		ofVec3f camTarget = ofVec3f(0.0, 0.0, 0.0);
		float aspect;
		ofShader renderShader;
		ofShader previewShader;
		ofShader shadowShader;
		ofMesh quad;

		//SceneGeometry
		ofPlanePrimitive plane;
		
		ofSpherePrimitive spheres[sphereNum];
		ofBoxPrimitive box;
};
