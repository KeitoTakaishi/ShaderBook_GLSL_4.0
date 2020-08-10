#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(false);
	ofSetFrameRate(60);

	initScene();
	initGUI();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(0.0);


	//shader.begin();
	cam.begin();
	ofMatrix4x4 model;
	ofMatrix4x4 view;
	ofMatrix4x4 proj;
	model.rotateRad(ofDegToRad(ofGetFrameNum()), 0, 1, 0);
	shader.setUniformMatrix4f("model", model);
	view = ofGetCurrentViewMatrix();
	shader.setUniformMatrix4f("view", view);
	shader.setUniformMatrix4f("proj", cam.getProjectionMatrix());
	shader.setUniform1i("type", 0);
	mesh.draw();

	model.makeIdentityMatrix();
	model.rotateRad(ofDegToRad(88), 1, 0, 0);
	model.setTranslation(0.0, -265.0, 0.0);
	shader.setUniformMatrix4f("model", model);
	shader.setUniform1i("type", 1);
	cam.end();

	//shader.end();

	ofDisableDepthTest();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::initScene() {
	shader.load("shaders/shader.vert", "shaders/shader.frag");
	model.loadModel("model/model.obj", true);
	model.setScale(100, 100, 100);
	model.enableNormals();
	mesh = model.getMesh(0);
	mesh.enableNormals();
}
//--------------------------------------------------------------
void ofApp::initGUI() {
	gui.setup();
	gui.add(_Ka.set("Mat_Ambient", ofVec3f(0.1, 0.1, 0.1), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(_Kd.set("Mat_Diffuse", ofVec3f(0.5, 0.5, 0.5), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(_Ks.set("Mat_Specular", ofVec3f(0.7, 0.7, 0.7), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(_shininess.set("shininess", 5.0, 0.0, 200.0));
}