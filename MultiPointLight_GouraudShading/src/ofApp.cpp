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
	gui.add(Ks.set("Ks", ofVec3f(1.0, 1.0, 1.0), ofVec3f(.0, .0, .0), ofVec3f(1.0, 1.0, 1.0)));
	gui.add(shininess.set("shininess", 5.0, 0.0, 200.0));
	gui.add(debug.setup("Debug", false));


	ofSetVerticalSync(false);
	ofSetFrameRate(60);



	//Ubo
	cout  <<  "GetProgram : " << shader.getProgram() << endl;
	ofLogNotice("----Uniform Valiables-----");
	shader.printActiveUniforms();
	ofLogNotice("----Uniform Blocks-----");
	shader.printActiveUniformBlocks();
	
	
	/*
	cout << "GL_MAX_UNIFORM_BUFFER_BINDINGS " << GL_MAX_UNIFORM_BUFFER_BINDINGS << endl;
	blockIndex_LightInfo = shader.getUniformBlockIndex("LightInfo ");
	glUniformBlockBinding(shader.getProgram(), blockIndex_LightInfo, 0);//FuckIII
	glGetActiveUniformBlockiv(shader.getProgram(), blockIndex_LightInfo, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize_LightInfo);
	blockBuffer_light = (GLubyte*)malloc(blockSize_LightInfo);
	const GLchar* names[] = {"LightInfo.Position", "LightInfo.La" , "LightInfo.Ld" , "LightInfo.Ls" };
	int n = 4;
	GLuint indices[4];
	glGetUniformIndices(shader.getProgram(), n, names, indices);
	GLint offset[4];
	glGetActiveUniformsiv(shader.getProgram(), n, indices, GL_UNIFORM_OFFSET, offset);
	
	ofVec4f lightPos = ofVec4f(1.0, 0.0, 0.0, 1.0);
	_La = ofVec4f(ofVec3f(La).x, ofVec3f(La).y, ofVec3f(La).z, 0.0);
	_Ld = ofVec4f(ofVec3f(Ld).x, ofVec3f(Ld).y, ofVec3f(Ld).z, 0.0);
	_Ls = ofVec4f(ofVec3f(Ls).x, ofVec3f(Ls).y, ofVec3f(Ls).z, 0.0);
	
	memcpy(blockBuffer_light + offset[0], &lightPos, 4 * sizeof(GLfloat));
	memcpy(blockBuffer_light + offset[1], &_La, 4 * sizeof(GLfloat));
	memcpy(blockBuffer_light + offset[2], &_Ld, 4 * sizeof(GLfloat));
	memcpy(blockBuffer_light + offset[3], &_Ls, 4 * sizeof(GLfloat));

	cout << offset[0] << endl;
	
	

	glGenBuffers(1, &uboHandle_LightInfo);
	glBindBuffer(GL_UNIFORM_BUFFER, uboHandle_LightInfo);
	glBufferData(GL_UNIFORM_BUFFER, blockSize_LightInfo, blockBuffer_light, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);


	//------------------------
	//Material
	
	blockIndex_MaterialInfo = shader.getUniformBlockIndex("MaterialInfo");
	glUniformBlockBinding(shader.getProgram(), blockIndex_MaterialInfo, 1);
	cout << "blockIndex_MaterialInfo : " << blockIndex_MaterialInfo << endl;
	glGetActiveUniformBlockiv(shader.getProgram(), blockIndex_MaterialInfo, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize_MaterialInfo);
	blockBuffer_material = (GLubyte*)malloc(blockSize_MaterialInfo);
	GLchar* names_material[] = { "MaterialInfo.Ka", "MaterialInfo.Kd", "MaterialInfo.Ks", "MaterialInfo.shininess"};
	n = 4;
	GLuint indices_material[4];
	GLint offset_material[4];
	glGetUniformIndices(shader.getProgram(), n, names_material, indices_material);
	glGetActiveUniformsiv(shader.getProgram(), n, indices_material, GL_UNIFORM_OFFSET, offset_material);
	_Ka = ofVec4f(ofVec3f(Ka).x, ofVec3f(Ka).y, ofVec3f(Ka).z, 0.0);
	_Kd = ofVec4f(ofVec3f(Kd).x, ofVec3f(Kd).y, ofVec3f(Kd).z, 0.0);
	_Ks = ofVec4f(ofVec3f(Ks).x, ofVec3f(Ks).y, ofVec3f(Ks).z, 0.0);

	float shininess = 1.0;
	memcpy(blockBuffer_material + offset_material[0], &_Ka, 4 * sizeof(GLfloat));
	memcpy(blockBuffer_material + offset_material[1], &_Kd, 4 * sizeof(GLfloat));
	memcpy(blockBuffer_material + offset_material[2], &_Ks, 4 * sizeof(GLfloat));
	memcpy(blockBuffer_material + offset[3], &shininess, sizeof(GLfloat));


	glGenBuffers(1, &uboHandle_MaterialInfo);
	glBindBuffer(GL_UNIFORM_BUFFER, uboHandle_MaterialInfo);
	glBufferData(GL_UNIFORM_BUFFER, blockSize_MaterialInfo, blockBuffer_material, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	

	cout << "blockIndex_LightInfo : " << blockIndex_LightInfo << endl;
	cout << "blockIndex_MaterialInfo : " << blockIndex_MaterialInfo << endl;
	*/
	
}

//--------------------------------------------------------------
void ofApp::update() {
	//ofSetWindowTitle(to_string(ofGetFrameRate()));

	float x = ofNoise(ofGetFrameNum() * 100.0) * 2.0 - 1.0;
	lightPos = ofVec3f(200.0 * cos(ofGetFrameNum() * 0.06), 150.0 * sin(ofGetFrameNum() * 0.05), 150.0 * cos(ofGetFrameNum() * 0.02));

	shininess = 1 + (sin(ofGetFrameNum() * 0.05) * 0.5 + 0.5) * 10.0;
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetBackgroundColor(0);
	ofEnableDepthTest();


	/*
	glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex_LightInfo, uboHandle_LightInfo);
	glUniformBlockBinding(shader.getProgram(), uboHandle_LightInfo, 0);
	_La = ofVec4f(ofVec3f(La).x, ofVec3f(La).y, ofVec3f(La).z, 1.0);
	_Ld = ofVec4f(ofVec3f(Ld).x, ofVec3f(Ld).y, ofVec3f(Ld).z, 1.0);
	_Ls = ofVec4f(ofVec3f(Ls).x, ofVec3f(Ls).y, ofVec3f(Ls).z, 1.0);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 + 16, 4 * sizeof(GLfloat), &_La);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 + 32, 4 * sizeof(GLfloat), &_Ld);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 + 48, 4 * sizeof(GLfloat), &_Ls);

	glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex_MaterialInfo, uboHandle_MaterialInfo);
	glUniformBlockBinding(shader.getProgram(), uboHandle_MaterialInfo, 1);
	_Ka = ofVec4f(ofVec3f(Ka).x, ofVec3f(Ka).y, ofVec3f(Ka).z, 0.0);
	_Kd = ofVec4f(ofVec3f(Kd).x, ofVec3f(Kd).y, ofVec3f(Kd).z, 0.0);
	_Ks = ofVec4f(ofVec3f(Ks).x, ofVec3f(Ks).y, ofVec3f(Ks).z, 0.0);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 , 4 * sizeof(GLfloat), &_Ka);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 + 16, 4 * sizeof(GLfloat), &_Kd);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 + 32, 4 * sizeof(GLfloat), &_Ks);
	*/
	

	shader.begin();
	shader.setUniform4f("light.La", ofVec4f(1.0, 0.0, 1.0, 1.0));
	/*shader.setUniform3f("_LightPos", ofVec3f(lightPos));
	shader.setUniform3f("_La", ofVec3f(La));
	shader.setUniform3f("_Ld", ofVec3f(Ld));
	shader.setUniform3f("_Ls", ofVec3f(Ls));
	shader.setUniform3f("_Ka", ofVec3f(Ka));
	shader.setUniform3f("_Kd", ofVec3f(Kd));
	shader.setUniform3f("_Ks", ofVec3f(Ks));
	shader.setUniform1f("_shininess", shininess);
	shader.setUniform1i("_debug", int(debug));*/




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

	glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex_LightInfo, 0);
	//glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex_MaterialInfo, 0);

	ofDisableDepthTest();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		shader.load("shaders/shader.vert", "shaders/shader.frag");
	}
}

