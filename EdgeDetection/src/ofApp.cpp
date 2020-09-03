#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	initScene();
	initFbo();
	
	gui.setup();
	gui.setup();
	gui.add(lightPosition.set("lightPosition", ofVec3f(0.0, 100., 0.), ofVec3f(-300., -300., -300.), ofVec3f(300., 300., 300.)));
	gui.add(lightIntensity.set("lightIntensity", ofVec3f(.6, .6, .6), ofVec3f(.0, .0, .0), ofVec3f(1., 1., 1.)));
	gui.add(Ka.set("Mat_Ambient", ofVec3f(0.6, 0.6, 0.6), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(Kd.set("Mat_Diffuse", ofVec3f(0.5, 0.5, 0.5), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(Ks.set("Mat_Specular", ofVec3f(0.54, 0.7, 0.7), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(shininess.set("shininess", 1.0, 0.0, 200.0));
	gui.add(EdgeThreshold.set("EdgeThreshold", 3.0, 0.0, 5.0));

	
}

//--------------------------------------------------------------
void ofApp::update() {
	float t = ofDegToRad(ofGetElapsedTimef())*25.0;
	float r = 750;
	cam.setPosition(r * cos(t), 0.0, r * sin(t));
	cam.lookAt(ofVec3f(0.0, 0.0, 0.0), ofVec3f(0.0, 1.0, 0.0));



	fbo.begin();
	ofBackground(70);
	ofEnableDepthTest();
	lightingShader.begin();
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &lightPass);
	cam.begin();
	ofMatrix4x4 model;
	ofMatrix4x4 view;
	ofMatrix4x4 proj;
	model.makeIdentityMatrix();
	model.rotateRad(PI, 0.0, 0.0, 1.0);
	view = ofGetCurrentViewMatrix();
	proj = cam.getProjectionMatrix();
	lightingShader.setUniformMatrix4f("model", model);
	lightingShader.setUniformMatrix4f("view", view);
	lightingShader.setUniformMatrix4f("proj", proj);
	lightingShader.setUniform3f("lightPosition", ofVec3f(lightPosition));
	lightingShader.setUniform3f("lightIntensity", ofVec3f(lightIntensity));
	lightingShader.setUniform3f("Ka", ofVec3f(Ka));
	lightingShader.setUniform3f("Kd", ofVec3f(Kd));
	lightingShader.setUniform3f("Ks", ofVec3f(Ks));
	lightingShader.setUniform1f("shininess", shininess);
	mesh.draw();

	cam.end();
	lightingShader.end();

	fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {
	//fbo.draw(0.0, 0.0, fbo.getWidth(), fbo.getHeight());

	edgeShader.begin();
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &edgeDetectionPass);
	edgeShader.setUniformTexture("tex0", fbo.getTexture(0), 0);
	edgeShader.setUniform2f("uRes", ofVec2f(ofGetWidth(), ofGetHeight()));
	edgeShader.setUniform1f("EdgeThreshold", EdgeThreshold);
	quad.draw();
	edgeShader.end();
	
	ofDisableDepthTest();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		lightingShader.load("shaders/passThru.vert", "shaders/shader.frag");
	}
}

//--------------------------------------------------------------
void ofApp::initScene() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	lightingShader.load("shaders/passThru.vert", "shaders/shader.frag");
	lightingShader.printActiveUniforms();

	GLuint prog = lightingShader.getProgram();
	lightPass = glGetSubroutineIndex(prog, GL_FRAGMENT_SHADER, "LightingPass");
	
	edgeShader.load("shaders/pass.vert", "shaders/shader.frag");
	prog = lightingShader.getProgram();
	edgeDetectionPass = glGetSubroutineIndex(prog, GL_FRAGMENT_SHADER, "EdgeDetectionPass");

	cout << "lightPass : " << lightPass << endl;
	cout << "edgeDetectionPass : " << edgeDetectionPass << endl;

	model.loadModel("model/model.obj", true);
	model.setScale(100, 100, 100);
	model.enableNormals();
	mesh = model.getMesh(0);
	mesh.enableNormals();
}
//--------------------------------------------------------------
void ofApp::initFbo() {
	fboSettings.width = ofGetWidth();
	fboSettings.height = ofGetHeight();
	fboSettings.numColorbuffers = 1;
	fboSettings.useDepth = true;
	fboSettings.internalformat = GL_RGBA;    
	fboSettings.wrapModeHorizontal = GL_CLAMP_TO_EDGE;
	fboSettings.wrapModeVertical = GL_CLAMP_TO_EDGE;
	fboSettings.minFilter = GL_NEAREST;
	fboSettings.maxFilter = GL_NEAREST;

	fbo.allocate(fboSettings);

	//final out
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