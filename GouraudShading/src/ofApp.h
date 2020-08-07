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
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		

		ofxAssimpModelLoader model;
		ofVboMesh mesh;
		ofShader shader;
		ofEasyCam cam;


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
