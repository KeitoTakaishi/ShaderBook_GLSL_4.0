#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	initScene();
	createCubeMapTex();

	gui.setup();
	gui.add(refrectFactor.set("ReflectFactor", 0.75, 0.75, 1.0));
	gui.add(materialColor.set("MaterialColor", ofFloatColor(0.7, 0.28, 0.28), ofFloatColor(0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0)));
}

//--------------------------------------------------------------
void ofApp::update() {
	float t = ofDegToRad(ofGetElapsedTimef())*25.0;
	float r = 750;
	cam.setPosition(r * cos(t), 0.0, r * sin(t));
	cam.lookAt(ofVec3f(0.0, 0.0, 0.0), ofVec3f(0.0, 1.0, 0.0));
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofEnableDepthTest();

	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	shader.begin();
	cam.begin();
	ofMatrix4x4 model;
	ofMatrix4x4 view;
	ofMatrix4x4 proj;
	view = ofGetCurrentViewMatrix();
	proj = cam.getProjectionMatrix();
	shader.setUniformMatrix4f("model", model);
	shader.setUniformMatrix4f("view", view);
	shader.setUniformMatrix4f("proj", proj);
	shader.setUniform1i("DrawSkyBox", 1);
	shader.setUniform1f("refrectFactor", refrectFactor);
	shader.setUniform3f("materialColor", ofVec3f(materialColor.get().r, materialColor.get().g, materialColor.get().b));
	shader.setUniform3f("worldCameraPos", cam.getPosition());

	mesh.draw();


	for (int i = 0; i < MODEL_NUM; i++) {
		float r = 500;
		if (i == 0) model.translate(-r, 0, 0);
		if (i == 1) model.translate(0, 0, 0);
		if (i == 2) model.translate(r, 0, 0);
		if (i == 3) model.translate(0, -r, 0);
		if (i == 4) model.translate(0, r, 0);
		if (i == 5) model.translate(0, 0, -r);
		if (i == 6) model.translate(0, 0, r);
		model.rotate(ofGetElapsedTimef() * 10, 1.0, 0.5, 0.0);
		sphere.setRadius(radiuses[i]);
		shader.setUniformMatrix4f("model", model);
		sphere.draw();
	}


	shader.setUniform1i("DrawSkyBox", 0);
	model.makeIdentityMatrix();
	shader.setUniformMatrix4f("model", model);
	box.draw();

	cam.end();
	shader.end();
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	ofDisableDepthTest();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		shader.load("shaders/shader.vert", "shaders/shader.frag");
	}
}

//--------------------------------------------------------------
void ofApp::initScene() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	shader.load("shaders/shader.vert", "shaders/shader.frag");
	model.loadModel("model/model.obj", true);
	model.setScale(100, 100, 100);
	model.enableNormals();
	mesh = model.getMesh(0);
	mesh.enableNormals();
	for (int i = 0; i < MODEL_NUM; i++) {
		radiuses[i] = ofRandom(20, 80);
	}
	box.set(1500);
	box.setResolution(32);

}
//--------------------------------------------------------------
void ofApp::createCubeMapTex() {
	/*
	1. TextureObject‚ð¶¬
	2. CubeMapTexture‚ðbind‚·‚é
	3. ‰æ‘œƒf[ƒ^‚ðLoad
	*/
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

	//load images
	img[0].load("textures/px.png");
	img[1].load("textures/nx.png");
	img[2].load("textures/py.png");
	img[3].load("textures/ny.png");
	img[4].load("textures/pz.png");
	img[5].load("textures/nz.png");

	//copy data to memory
	auto size = ofVec2f(img[0].getWidth(), img[0].getHeight());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img[0].getPixels().getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img[1].getPixels().getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img[2].getPixels().getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img[3].getPixels().getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img[4].getPixels().getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img[5].getPixels().getData());


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}