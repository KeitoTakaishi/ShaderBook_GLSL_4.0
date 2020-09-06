#include "ofApp.h"

/*
- getDepthTexture()
- useDepthStencil
- canNearTexture
*/

//--------------------------------------------------------------
void ofApp::setup(){
	aspect = ofGetWidth() / ofGetHeight();
	renderShader.load("shaders/passThru.vert", "shaders/constColor.frag");
	previewShader.load("shaders/previewQuad.vert", "shaders/previewQuad.frag");
	shadowShader.load("shaders/shadowMap.vert", "shaders/shadowMap.frag");
	//scene geometry
	plane.set(1000, 1000);
	for (int i = 0; i < sphereNum; i++) {
		spheres[i].setRadius(30);
	}
	box.set(200);
	shadowMap = new ShadowMap();


	//quad
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


	
	cout << "num textures : " << shadowMap->depthFbo.getNumTextures() << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
	
	ofEnableDepthTest();
	glEnable(GL_CULL_FACE);
	
	shadowMap->renderDepthBegin();
	shadowMap->camBegin();
	//render2Fbo(renderShader);//off screen rendering-------------------------------
	renderShader.begin();
	ofMatrix4x4 m, v, p;

	ofEasyCam& c = shadowMap->lightCam;
	v = getViewMatrix(c.getGlobalPosition(), shadowMap->camUp, shadowMap->camTarget);
	p = getProjMatrix(c.getFov(), aspect, c.getNearClip(), c.getFarClip());
	renderShader.setUniformMatrix4f("view", v);
	renderShader.setUniformMatrix4f("proj", p);

	m.rotateRad(PI / 2.0, 1.0, 0.0, 0.0);
	renderShader.setUniformMatrix4f("model", m);
	plane.draw();

	float theta = TWO_PI / sphereNum;
	float r = 300.0;
	for (int i = 0; i < sphereNum; i++) {
		m.makeIdentityMatrix();
		m.setTranslation(r * cos(theta * i), 200.0 * sin( (i+0.0*ofGetFrameNum()) * 0.1), r * sin(theta * i));
		renderShader.setUniformMatrix4f("model", m);
		spheres[i].draw();
	}
	m.makeIdentityMatrix();
	m.rotateRad(ofGetFrameNum() * DEG_TO_RAD * 0.2, 1.0, 1.0, 1.0);
	m.setTranslation(0.0, 50.0, 0.0);
	renderShader.setUniformMatrix4f("model", m);
	box.draw();

	renderShader.end();
	//-------------------------------------------------------------------------------
	shadowMap->camEnd();
	shadowMap->renderDepthEnd();
	
	glDisable(GL_CULL_FACE);
	ofDisableDepthTest();
	

}

//--------------------------------------------------------------
void ofApp::draw(){
	glPolygonOffset(1.0, 1.0);
	//2D‚Å‚Í¶ã‚ª0.0‚È‚Ì‚Å”½“]‚µ‚Ä‚é
	//shadowMap->drawDepthFbo();
	ofEnableDepthTest();
	
	cam.begin();
	shadowMap->drawLight();
	ofDrawAxis(3000);

	shadowShader.begin();
	ofMatrix4x4 m, v, p;
	v = getViewMatrix(cam.getGlobalPosition(), shadowMap->camUp, shadowMap->camTarget);
	p = getProjMatrix(cam.getFov(), aspect, cam.getNearClip(), cam.getFarClip());
	

	//lightMatrix
	auto b = shadowMap->biasMatrix;
	auto vl = getViewMatrix(shadowMap->lightPos, shadowMap->camUp, shadowMap->camTarget);
	auto vp = getProjMatrix(shadowMap->lightCam.getFov(), aspect,
		shadowMap->lightCam.getNearClip(), shadowMap->lightCam.getFarClip());
	ofMatrix4x4 shadowMatrix = vl * vp * b;

	shadowShader.setUniformMatrix4f("shadowMatrix", shadowMatrix);
	shadowShader.setUniform3f("lightPos", shadowMap->lightPos);
	shadowShader.setUniformMatrix4f("view", v);
	shadowShader.setUniformMatrix4f("proj", p);

	m.rotateRad(PI / 2.0, 1.0, 0.0, 0.0);
	shadowShader.setUniformMatrix4f("model", m);
	shadowShader.setUniform1i("geomType", 1);
	plane.draw();


	shadowShader.setUniform1i("geomType", 0);
	float theta = TWO_PI / sphereNum;
	float r = 500.0;
	for (int i = 0; i < sphereNum; i++) {
		m.makeIdentityMatrix();
		m.setTranslation(r * cos(theta * i), 200.0 * sin((i + 0.0*ofGetFrameNum()) * 0.1), r * sin(theta * i));
		shadowShader.setUniformMatrix4f("model", m);
		spheres[i].draw();
	}

	m.makeIdentityMatrix();
	m.rotateRad(ofGetFrameNum() * DEG_TO_RAD * 0.2, 1.0, 1.0, 1.0);
	m.setTranslation(0.0, 50.0, 0.0);
	shadowShader.setUniformMatrix4f("model", m);
	box.draw();

	shadowShader.end();

	cam.end();
	

	previewShader.begin();
	previewShader.setUniformTexture("tex0", shadowMap->depthFbo.getDepthTexture(), 0);
	previewShader.setUniform2f("uRes", ofVec2f(ofGetWidth(), ofGetHeight()));

	quad.draw();
	previewShader.end();
	

	ofDisableDepthTest();

	//ofBackground(0.0);
	//shadowMap->drawDepthFbo();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (' ') {
		renderShader.load("shaders/passThru.vert", "shaders/constColor.frag");
		previewShader.load("shaders/previewQuad.vert", "shaders/previewQuad.frag");
		shadowShader.load("shaders/shadowMap.vert", "shaders/shadowMap.frag");
	}
}
//--------------------------------------------------------------
void ofApp::render2Fbo(ofShader& shader) {
	shader.begin();
	ofMatrix4x4 m, v, p;
	
	v = getViewMatrix(cam.getGlobalPosition(), camUp, camTarget);
	p = getProjMatrix(cam.getFov(), aspect, cam.getNearClip(), cam.getFarClip());
	shader.setUniformMatrix4f("view", v);
	shader.setUniformMatrix4f("proj", p);
	
	m.rotateRad(PI/2.0, 1.0, 0.0, 0.0);
	shader.setUniformMatrix4f("model", m);
	plane.draw();
	

	float theta = TWO_PI / 6.0;
	float r = 300.0;
	for (int i = 0; i < 6; i++) {
		m.makeIdentityMatrix();
		m.setTranslation(r * cos(theta * i), 50.0, r * sin(theta * i));
		shader.setUniformMatrix4f("model", m);
		spheres[i].draw();
	}
	shader.end();
	
	
}