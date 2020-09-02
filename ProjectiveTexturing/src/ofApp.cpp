#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	initGui();
	setupProjector();
	createTexture();
	shader.load("shaders/shader.vert", "shaders/shader.frag");
	shader.printActiveUniforms();
	bias = ofMatrix4x4(0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0);
}

//--------------------------------------------------------------
void ofApp::update() {
	setupProjector();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);
	
	ofEnableDepthTest();

	shader.begin();

	//projector
	shader.setUniformMatrix4f("bias", bias);
	shader.setUniformMatrix4f("pVM", projctor.getModelViewMatrix());
	shader.setUniformMatrix4f("pP", projctor.getProjectionMatrix());

	cam.begin();
	ofMatrix4x4 model, view, proj;
	view = ofGetCurrentViewMatrix();
	proj = cam.getProjectionMatrix();
	shader.setUniformMatrix4f("model", model);
	shader.setUniformMatrix4f("view", view);
	shader.setUniformMatrix4f("proj", proj);




	//loc = glGetUniformLocation(shader.getProgram(), "tex");
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texID);
	shader.setUniformTexture("tex", img.getTexture(), 0);
	//glUniform1i(loc, 0);


	box.draw();
	shader.end();
	ofDrawAxis(1000);
	sphere.setPosition(projPos.get());
	sphere.draw();
	cam.end();

	ofDisableDepthTest();
	projectorGui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		shader.load("shaders/shader.vert", "shaders/shader.frag");
	}
}

//--------------------------------------------------------------
void ofApp::initGui() {
	projectorGui.setup();
	projectorGui.setName("projector_params");
	projectorGui.add(projPos.set("projPos", ofVec3f(0.0, 1000, 0.0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000.0, 1000, 1000)));
	projectorGui.add(projClip.set("projClip", ofVec2f(0.1, 1000), ofVec2f(0.0, 10), ofVec2f(10.0, 1000)));
	projectorGui.add(projFov.set("projFov", 90.0, 0.0, 180.0));
}
//--------------------------------------------------------------
void ofApp::createTexture() {
	ofDisableArbTex();
	//TEXTURE_Unit : 0 <- texID
	cout << ofGetUsingArbTex() << endl;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	img.load("texture/tex.jpg");
	/*
	ofVec2f size = ofVec2f(img.getWidth(), img.getHeight());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixels().getData());
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	*/
}
//--------------------------------------------------------------
void ofApp::setupProjector() {
	projctor.setupPerspective();
	projctor.setPosition(projPos.get());
	projctor.setNearClip(projClip->x);
	projctor.setFarClip(projClip->y);
	projctor.lookAt(ofVec3f(0.0, 0.0, 0.0));
	projctor.setFov(projFov);
	//cam.setForceAspectRatio(1.0);
}
