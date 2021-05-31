#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	preload();
	initBaseScene();
	initGUI();
	initFbo();


	biasMatrix.set(0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0);

	/*
	//MAtrix calculation test
	ofVec4f v = ofVec4f(-1.0, -1.0, -1.0, 1.0);
	cout << v * biasMatrix << endl;
	*/
}

//--------------------------------------------------------------
void ofApp::update() {


	//offScreenRender
	ofEnableDepthTest();
	renderFbo.begin();
	ofClear(0);
	lightProjector.begin();
	setLightParames();
	drawWall(lightProjector, debugShader);
	drawSceneElements(lightProjector, debugShader);
	lightProjector.end();
	renderFbo.end();
	ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofClear(0);
	ofBackground(0);


	ofEnableDepthTest();
	cam.begin();
	drawWall(cam, shadowShader);
	drawSceneElements(cam, shadowShader);


	//light
	previewLight();
	cam.end();


	//preview shadow
	previewShader.begin();
	ofMatrix4x4 m, v, p;
	m.makeIdentityMatrix();
	v = ofGetCurrentViewMatrix();
	p = cam.getProjectionMatrix();
	//previewShader.setUniformMatrix4f("model", m);
	//previewShader.setUniformMatrix4f("view", v);
	//previewShader.setUniformMatrix4f("proj", p);


	//previewShader.setUniformTexture("tex0", renderFbo.getTexture(0), 0);
	previewShader.setUniformTexture("tex0", renderFbo.getDepthTexture(), 0);
	previewShader.setUniform2f("uRes", ofVec2f(ofGetWidth(), ofGetHeight()));
	quad.draw();
	previewShader.end();



	//renderFbo.draw(0.0, 0.0);
	ofDisableDepthTest();
	lightGui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		debugShader.load("shaders/passThru.vert", "shaders/constColor.frag");
		previewShader.load("shaders/previewQuad.vert", "shaders/previewQuad.frag");
		shadowShader.load("shaders/shadowMap.vert", "shaders/shadowMap.frag");
	}
}
//--------------------------------------------------------------
void ofApp::preload() {
	debugShader.load("shaders/passThru.vert", "shaders/constColor.frag");
	previewShader.load("shaders/previewQuad.vert", "shaders/previewQuad.frag");
	shadowShader.load("shaders/shadowMap.vert", "shaders/shadowMap.frag");
}
//--------------------------------------------------------------
void ofApp::initGUI() {
	lightGui.setup();
	lightGui.setName("light GUI");
	lightGui.add(lightPos.set("light pos", ofVec3f(400, 400, 200.0), ofVec3f(-600, -600, -600.0), ofVec3f(600, 600, 600.0)));
	lightGui.add(lightProjClip.set("light proj clip", ofVec2f(10.0, 700.0), ofVec2f(0.1, 30.0), ofVec2f(30.0, 3000.0)));
	lightGui.add(lightProjFov.set("light proj fov", 60.0, 0.0, 180.0));

}
//--------------------------------------------------------------
void ofApp::initFbo() {
	ofFboSettings *fboSettings;
	fboSettings = new ofFboSettings();
	fboSettings->width = ofGetWidth();
	fboSettings->height = ofGetHeight();
	fboSettings->numColorbuffers = 0;
	fboSettings->useDepth = true;
	fboSettings->depthStencilAsTexture = true;
	fboSettings->internalformat = GL_RGBA;
	fboSettings->depthStencilInternalFormat = GL_DEPTH_COMPONENT32;
	fboSettings->wrapModeHorizontal = GL_CLAMP_TO_EDGE;
	fboSettings->wrapModeVertical = GL_CLAMP_TO_EDGE;
	fboSettings->minFilter = GL_NEAREST;
	fboSettings->maxFilter = GL_NEAREST;
	renderFbo.allocate(*fboSettings);
	delete fboSettings;


	quad.addVertex(ofVec3f(-1.0, -1.0));
	quad.addVertex(ofVec3f(-1.0, 1.0));
	quad.addVertex(ofVec3f(1.0, 1.0));
	quad.addVertex(ofVec3f(1.0, -1.0));

	quad.addTexCoord(ofVec2f(.0, .0));
	quad.addTexCoord(ofVec2f(.0, 1.0));
	quad.addTexCoord(ofVec2f(1.0, 1.0));
	quad.addTexCoord(ofVec2f(1.0, .0));

	quad.addIndex(0);
	quad.addIndex(1);
	quad.addIndex(2);

	quad.addIndex(2);
	quad.addIndex(3);
	quad.addIndex(0);
}
//--------------------------------------------------------------
void ofApp::initBaseScene() {
	wall[0].set(wallSize, wallSize);
	wall[1].set(wallSize, wallSize);
	wall[2].set(wallSize, wallSize);

	//other Objects
	for (int i = 0; i < SPHERE_NUN; i++) {
		spherePos[i] = ofVec3f(ofRandom(-300, 300), ofRandom(30, 100), ofRandom(-300, 300));
		sphereRadius[i] = ofRandom(5.0, 10.0);

	}

	for (int i = 0; i < BOX_NUN; i++) {
		boxPos[i] = ofVec3f(ofRandom(-300, 300), ofRandom(0, 100), ofRandom(-300, 300));
		boxScale[i] = ofVec3f(ofRandom(20, 50), ofRandom(20, 50), ofRandom(20, 50));
	}
}
//--------------------------------------------------------------
void ofApp::drawWall(ofEasyCam& cam, ofShader& shader) {
	ofMatrix4x4 m, v, p;
	v = ofGetCurrentViewMatrix();
	p = cam.getProjectionMatrix();

	shader.begin();
	shader.setUniformMatrix4f("view", v);
	shader.setUniformMatrix4f("proj", p);


	m.rotateRad(HALF_PI, 1.0, 0.0, 0.0);
	shader.setUniformMatrix4f("model", m);
	wall[0].draw();
	m.makeIdentityMatrix();
	m.setTranslation(ofVec3f(0.0, wallSize*0.5, -wallSize*0.5));
	shader.setUniformMatrix4f("model", m);
	wall[1].draw();
	m.makeIdentityMatrix();
	m.rotateRad(HALF_PI, 0.0, 1.0, 0.0);
	m.setTranslation(ofVec3f(wallSize*0.5, wallSize*0.5, 0.0));
	shader.setUniformMatrix4f("model", m);
	wall[2].draw();


	//wall[1].set(500, 500);
	//wall[2].set(500, 500);
	shader.end();
}
//--------------------------------------------------------------
void ofApp::drawSceneElements(ofEasyCam& cam, ofShader& shader) {
	ofMatrix4x4 m, v, p;

	v = ofGetCurrentViewMatrix();
	p = cam.getProjectionMatrix();

	shader.begin();
	shader.setUniformMatrix4f("view", v);
	shader.setUniformMatrix4f("proj", p);



	//shader.setUniformMatrix4f("shadowMat", lightProjector.getModelViewMatrix()*lightProjector.getProjectionMatrix()*biasMatrix);
	//lightProjector.getModelViewMatrix();
	//lightProjector.getProjectionMatrix();
	lightProjector.getModelViewProjectionMatrix();

	//cout << "---------------------" << endl;
	//cout << lightProjector.getModelViewMatrix() << endl;


	for (int i = 0; i < SPHERE_NUN; i++) {
		m.makeIdentityMatrix();
		m.setTranslation(spherePos[i]);
		m.scale(ofVec3f(2.0));
		shader.setUniformMatrix4f("model", m);
		spheres[i].draw();
	}
	shader.end();
}
//--------------------------------------------------------------
void ofApp::setLightParames() {
	lightProjector.setPosition(lightPos.get());
	lightProjector.lookAt(ofVec3f(0.0, 0.0, 0.0), ofVec3f(0.0, -1.0, 0.0));
	lightProjector.setFarClip(lightProjClip.get().x);
	lightProjector.setFarClip(lightProjClip.get().y);
	lightProjector.setFov(lightProjFov);
}
//--------------------------------------------------------------
void ofApp::previewLight() {
	ofDrawAxis(5000);
	lightObj.setPosition(lightPos.get());
	ofPushStyle();
	ofSetColor(255, 0.0, 0.);
	lightObj.draw();
	lightProjector.drawFrustum();
	ofPopStyle();
}
