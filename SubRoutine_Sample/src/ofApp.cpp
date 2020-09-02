#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	float r = 300;
	for (int i = 0; i < NUM; i++) {
		float s = ofRandom(20, 80);
		//box[i].set(ofVec3f(s, s, s);
		box[i].set(s);
		pos[i] = ofVec3f(ofRandom(-r, r), ofRandom(-r, r), ofRandom(-r, r));
	}

	shader.load("shaders/shader.vert", "shaders/shader.frag");
	redPass = glGetSubroutineIndex(shader.getProgram(), GL_FRAGMENT_SHADER, "redPass");
	greenPass = glGetSubroutineIndex(shader.getProgram(), GL_FRAGMENT_SHADER, "greenPass");
	bluePass = glGetSubroutineIndex(shader.getProgram(), GL_FRAGMENT_SHADER, "bluePass");
	cout << redPass << endl;
	cout << greenPass << endl;
	cout << bluePass << endl;

}

//--------------------------------------------------------------
void ofApp::update() {

}
//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(50);
	shader.begin();
	cam.begin();
	ofMatrix4x4 m, v, p;
	v = ofGetCurrentViewMatrix();//what is matrix mode?
	p = cam.getProjectionMatrix();
	for (int i = 0; i < NUM; i++) {
		//box[i].draw();
		box[i].drawWireframe();
		m.makeIdentityMatrix();
		m.rotate(ofDegToRad(ofGetFrameNum() * 10.0), 1, 1, 1);
		m.setTranslation(pos[i]);
		shader.setUniformMatrix4f("model", m);

		if (i < 3) {
			glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &redPass);
		}
		else if (i >= 3 && i < 6) {
			glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &greenPass);
		}
		else  if (i >= 6) {
			glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &bluePass);
		}
	}
	shader.setUniformMatrix4f("view", v);
	shader.setUniformMatrix4f("proj", p);


	cam.end();
	shader.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
