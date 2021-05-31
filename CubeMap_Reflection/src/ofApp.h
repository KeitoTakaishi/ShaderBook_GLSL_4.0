#pragma once
#define MODEL_NUM 7

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
		void createCubeMapTex();
		


		//Scene
		ofSpherePrimitive sphere;
		ofBoxPrimitive box;
		float radiuses[MODEL_NUM];
		ofxAssimpModelLoader model;
		ofVboMesh mesh;
		ofShader shader;
		ofEasyCam cam;

		ofxPanel gui;
		ofParameter<float> refrectFactor;
		ofParameter<ofFloatColor> materialColor;
		
		//CubeMap
		GLuint texID;
		ofImage img[6];
		GLuint uniLoc;
		
};
