#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void initScene();
		void createCubeMapTex();
		


		//Scene
		ofxAssimpModelLoader model;
		ofVboMesh mesh;
		ofShader shader;
		ofEasyCam cam;

		//CubeMap
		GLuint texID;
		ofImage img[6];
		
};
