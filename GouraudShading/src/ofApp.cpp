#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	shader.load("shaders/shader.vert", "shaders/shader.frag");

	
	model.loadModel("model/model.obj", true);
	model.setScale(100, 100, 100);
	model.enableNormals();
	
	mesh = model.getMesh(0);
	mesh.enableNormals();


	gui.setup();
	gui.add(lightPos.set("LightPos", ofVec3f(100, 100, 0.0), ofVec3f(-300, -300, -300.0), ofVec3f(300, 300, 300.0)));
	gui.add(La.set("La", ofVec3f(0.15, 0.2, 0.2), ofVec3f(0.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(Ld.set("Ld", ofVec3f(0.5, 0.51, 0.75), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(Ls.set("Ls", ofVec3f(0.5, 0.8, 1.0), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(Ka.set("Ka", ofVec3f(0.5, 0.5, 0.5), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(Kd.set("Kd", ofVec3f(0.75, 0.75, 0.75), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(Ks.set("Ls", ofVec3f(1.0, 1.0, 1.0), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(shininess.set("shininess", 5.0, 0.0, 200.0));
	gui.add(debug.setup("Debug", false));


	ofSetVerticalSync(false);
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
	//ofSetWindowTitle(to_string(ofGetFrameRate()));

	float x = ofNoise(ofGetFrameNum() * 100.0) * 2.0 - 1.0;
	lightPos = ofVec3f(200.0 * cos(ofGetFrameNum() * 0.06), 150.0 * sin(ofGetFrameNum() * 0.05), 150.0 * cos(ofGetFrameNum() * 0.02));

	shininess = 1 + (sin(ofGetFrameNum() * 0.05) * 0.5 + 0.5) * 10.0;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(0);
	ofEnableDepthTest();


	shader.begin();
	shader.setUniform3f("_LightPos", ofVec3f(lightPos));
	shader.setUniform3f("_La", ofVec3f(La));
	shader.setUniform3f("_Ld", ofVec3f(Ld));
	shader.setUniform3f("_Ls", ofVec3f(Ls));
	shader.setUniform3f("_Ka", ofVec3f(Ka));
	shader.setUniform3f("_Kd", ofVec3f(Kd));
	shader.setUniform3f("_Ks", ofVec3f(Ks));
	shader.setUniform1f("_shininess", shininess);
	shader.setUniform1i("_debug", int(debug));
	

	
	cam.begin();
	ofMatrix4x4 model;
	model.rotateRad(ofGetFrameNum() * 0.01, 0.0, 1.0, 0.0);
	ofMatrix4x4 view;
	ofMatrix4x4 proj;
	shader.setUniformMatrix4f("model", model);
	view = ofGetCurrentViewMatrix();
	shader.setUniformMatrix4f("view", view);
	shader.setUniformMatrix4f("proj", cam.getProjectionMatrix());
	mesh.draw();
	cam.end();
	shader.end();

	ofDisableDepthTest();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		shader.load("shaders/shader.vert", "shaders/shader.frag");
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
