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
	ofEnableDepthTest();

	shader.begin();
	cam.begin();
	ofMatrix4x4 model;
	ofMatrix4x4 view;
	ofMatrix4x4 proj;
	model.rotateRad(ofDegToRad(ofGetFrameNum()), 0, 1, 0);
	shader.setUniformMatrix4f("model", model);
	view = ofGetCurrentViewMatrix();
	shader.setUniformMatrix4f("view", view);
	shader.setUniformMatrix4f("proj", cam.getProjectionMatrix());
	shader.setUniform3f("lightPosition", ofVec3f(lightPosition));
	shader.setUniform3f("lightIntensity", ofVec3f(lightIntensity));
	shader.setUniform3f("Ka", ofVec3f(Ka));
	shader.setUniform3f("Kd", ofVec3f(Kd));
	shader.setUniform3f("Ks", ofVec3f(Ks));
	shader.setUniform1f("shininess", shininess);
	shader.setUniform1i("optimize", int(optimize));

	mesh.draw();

	
	cam.end();
	shader.end();

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
	gui.add(lightPosition.set("lightPosition", ofVec3f(0.0, 100., 0.), ofVec3f(-300., -300., -300.), ofVec3f(300., 300., 300.)));
	gui.add(lightIntensity.set("lightIntensity", ofVec3f(.6, .6, .6), ofVec3f(.0, .0, .0), ofVec3f(1., 1., 1.)));
	gui.add(Ka.set("Mat_Ambient", ofVec3f(0.6, 0.6, 0.6), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(Kd.set("Mat_Diffuse", ofVec3f(0.5, 0.5, 0.5), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(Ks.set("Mat_Specular", ofVec3f(0.54, 0.7, 0.7), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(shininess.set("shininess", 5.0, 0.0, 200.0));
	gui.add(optimize.setup("optimize", false));
}