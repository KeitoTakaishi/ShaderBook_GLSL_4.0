#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(false);
	ofSetFrameRate(60);

	initScene();
	initLight();
	initGUI();
	createUBO();
	
	shader.printActiveUniforms();
}

//--------------------------------------------------------------
void ofApp::update() {
	Ka = ofVec4f(ofVec3f(_Ka).x, ofVec3f(_Ka).y, ofVec3f(_Ka).z, 0.0);
	Kd = ofVec4f(ofVec3f(_Kd).x, ofVec3f(_Kd).y, ofVec3f(_Kd).z, 0.0);
	Ks = ofVec4f(ofVec3f(_Ks).x, ofVec3f(_Ks).y, ofVec3f(_Ks).z, 0.0);
	shininess = _shininess;
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackgroundGradient(startColor, endColor, OF_GRADIENT_CIRCULAR);
	ofEnableDepthTest();

	shader.begin();
	glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, uboHandle);
	glUniformBlockBinding(programHandle, uboHandle, 0);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 4 * sizeof(GLfloat), &Ka);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 + 16, 4 * sizeof(GLfloat), &Kd);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 + 32, 4 * sizeof(GLfloat), &Ks);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 + 48, sizeof(GLfloat), &shininess);
	for (int i = 0; i < LIGHT_NUM; i++) {
		auto name = "lightInfo[" + to_string(i) + "].position";
		shader.setUniform3f(name, lightInfo[i].position);
		name = "lightInfo[" + to_string(i) + "].intensity";
		shader.setUniform3f(name, lightInfo[i].intensity);
	}
	
	
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
	//plane.draw();
	cam.end();
	glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, 0);
	shader.end();
	
	

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
	shader.load("shaders/shader.vert", "shaders/shader.frag");
	model.loadModel("model/model.obj", true);
	model.setScale(100, 100, 100);
	model.enableNormals();
	mesh = model.getMesh(0);
	mesh.enableNormals();

	plane.set(5000, 5000);
	plane.setResolution(100, 100);
}
//--------------------------------------------------------------
void ofApp::initLight() {
	float range = 10000;
	for (int i = 0; i < LIGHT_NUM; i++) {
		lightInfo[i].position = ofVec3f(ofRandom(-range, range), ofRandom(-range, range), ofRandom(-range, range));
		lightInfo[i].intensity = ofVec3f(ofRandom(0.4), ofRandom(0.4), ofRandom(0.4));
		auto name = "lightInfo[" + to_string(i) + "].position";
		ofLogNotice(name + " : " + ofToString(lightInfo[i].position));
		name = "lightInfo[" + to_string(i) + "].intensity";
		ofLogNotice(name + " : " + ofToString(lightInfo[i].intensity));
	}
}
//--------------------------------------------------------------
void ofApp::initGUI() {
	gui.setup();
	gui.add(_Ka.set("Mat_Ambient", ofVec3f(0.1, 0.1, 0.1), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(_Kd.set("Mat_Diffuse", ofVec3f(0.5, 0.5, 0.5), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(_Ks.set("Mat_Specular", ofVec3f(0.7, 0.7, 0.7), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(_shininess.set("shininess", 5.0, 0.0, 200.0));
	gui.add(startColor.set("start color", ofColor(54, 230, 140), ofColor(0, 0), ofColor(255, 255)));
	gui.add(endColor.set("end color", ofColor(255, 140, 0), ofColor(0, 0), ofColor(255, 255)));
}
//--------------------------------------------------------------
void ofApp::createUBO() {
	programHandle = shader.getProgram();
	ofLogNotice("ProgramHandle : " + to_string(programHandle));

	shader.printActiveUniformBlocks();
	
	//bind
	string key = "MaterialInfo";
	blockIndex = shader.getUniformBlockIndex(key);
	//ID
	glUniformBlockBinding(programHandle, blockIndex, 0);
	//get UBO data size
	glGetActiveUniformBlockiv(programHandle, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
	cout << "DataSize : " << blockSize << endl;
	blockBuffer= (GLubyte*)malloc(blockSize);


	//get byte offset
	GLchar* names[] = { "MaterialInfo.Ka", "MaterialInfo.Kd", "MaterialInfo.Ks", "MaterialInfo.shininess" };
	GLuint indices[4];
	GLint offset[4];
	glGetUniformIndices(programHandle, 4, names, indices);
	glGetActiveUniformsiv(shader.getProgram(), 4, indices, GL_UNIFORM_OFFSET, offset);
	for (int i = 0; i < 4; i++) {
		cout << "Byte OffSet : " << offset[i] << endl;
	}

	//set data (-> temporary buffer)
	Ka = ofVec4f(0.5, 0.5, 0.5, 0.0);
	Kd = ofVec4f(0.75, 0.75, 0.75, 0.0);
	Ks = ofVec4f(1.0, 1.0, 1.0, 0.0);

	memcpy(blockBuffer + offset[0], &Ka, 4 * sizeof(GLfloat));
	memcpy(blockBuffer + offset[1], &Kd, 4 * sizeof(GLfloat));
	memcpy(blockBuffer + offset[2], &Ks, 4 * sizeof(GLfloat));
	memcpy(blockBuffer + offset[3], &shininess, sizeof(GLfloat));

	//create buffer and set data
	glGenBuffers(1, &uboHandle);
	glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
	glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
