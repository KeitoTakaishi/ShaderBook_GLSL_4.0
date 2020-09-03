#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	initScene();
	initFbo();
	initGUI();
}

//--------------------------------------------------------------
void ofApp::update(){
	calcBlurParam();

	float t = ofDegToRad(ofGetElapsedTimef())*25.0;
	float r = 750;
	cam.setPosition(r * cos(t), 0.0, r * sin(t));
	cam.lookAt(ofVec3f(0.0, 0.0, 0.0), ofVec3f(0.0, 1.0, 0.0));


	//1pass
	renderFbo.begin();
	ofBackground(20);
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
	renderFbo.end();


	//2pass
	blurFbo.begin();
	blurShader.begin();
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &FirstBlurPass);
	blurShader.setUniformTexture("tex0", renderFbo.getTexture(0), 0);
	blurShader.setUniform2f("uRes", ofVec2f(ofGetWidth(), ofGetHeight()));
	blurShader.setUniform1f("InverseUv", 0.0);
	for (int i = 1; i < 5; i++) {
		blurShader.setUniform1fv("weight", weights, 5);
	}
	quad.draw();
	blurShader.end();
	blurFbo.end();
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	//renderFbo.draw(0, 0, renderFbo.getWidth(), renderFbo.getHeight());

	
	blurShader.begin();
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &FirstBlurPass);
	blurShader.setUniformTexture("tex0", blurFbo.getTexture(0), 0);
	blurShader.setUniform2f("uRes", ofVec2f(ofGetWidth(), ofGetHeight()));
	blurShader.setUniform1f("InverseUv", 1.0);
	for (int i = 1; i < 5; i++) {
		blurShader.setUniform1fv("weight", weights, 5);
	}
	//quad.draw();
	blurShader.end();
	

	blurFbo.draw(0.0, 0.0, blurFbo.getWidth(), blurFbo.getHeight());
	ofDisableDepthTest();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		lightingShader.load("shaders/passThru.vert", "shaders/shader.frag");
	}
}

//--------------------------------------------------------------
void ofApp::calcBlurParam() {
	weights[0] = gauss(0, sigma2);
	sum = weights[0];
	for (int i = 1; i < 5; i++) {
		weights[i] = gauss(i, sigma2);
		sum += 2.0 * weights[i];
	}
}
//--------------------------------------------------------------
float ofApp::gauss(float x, float sigma2) {
	//return exp(-(x*x) / (2.0*sigma*sigma)) / sqrt(2.0 * PI * sigma * sigma);
	return exp(-(x*x) / (2.0*sigma2)) / sqrt(2.0 * PI * sigma2);
}

//--------------------------------------------------------------
void ofApp::initScene() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	lightingShader.load("shaders/passThru.vert", "shaders/shader.frag");
	

	
	GLuint prog = lightingShader.getProgram();
	lightPass = glGetSubroutineIndex(prog, GL_FRAGMENT_SHADER, "LightingPass");

	blurShader.load("shaders/pass.vert", "shaders/shader.frag");
	prog = blurShader.getProgram();
	FirstBlurPass = glGetSubroutineIndex(prog, GL_FRAGMENT_SHADER, "VertBlurPass");
	SecondBlurPass = glGetSubroutineIndex(prog, GL_FRAGMENT_SHADER, "SecondBlurPass");

	cout << "lightPass : " << lightPass << endl;
	cout << "VertBlurPass : " << FirstBlurPass << endl;
	cout << "SecondBlurPass : " << SecondBlurPass << endl;
	

	model.loadModel("model/model.obj", true);
	model.setScale(100, 100, 100);
	model.enableNormals();
	mesh = model.getMesh(0);
	mesh.enableNormals();
}
//--------------------------------------------------------------
void ofApp::initGUI() {
	gui.setup();
	gui.setup();
	gui.add(lightPosition.set("lightPosition", ofVec3f(0.0, 100., 0.), ofVec3f(-300., -300., -300.), ofVec3f(300., 300., 300.)));
	gui.add(lightIntensity.set("lightIntensity", ofVec3f(.6, .6, .6), ofVec3f(.0, .0, .0), ofVec3f(1., 1., 1.)));
	gui.add(Ka.set("Mat_Ambient", ofVec3f(0.6, 0.6, 0.6), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(Kd.set("Mat_Diffuse", ofVec3f(0.5, 0.5, 0.5), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(Ks.set("Mat_Specular", ofVec3f(0.54, 0.7, 0.7), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(shininess.set("shininess", 1.0, 0.0, 200.0));
	gui.add(sigma2.set("sigma2", 4.0, 0.0, 64.0));
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

	renderFbo.allocate(fboSettings);

	fboSettings.useDepth = false;
	blurFbo.allocate(fboSettings);

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