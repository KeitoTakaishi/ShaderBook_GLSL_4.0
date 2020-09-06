#include "ShadowMap.h"



ShadowMap::ShadowMap()
{
	cout << "Allocate Depth Buffer Fbo" << endl;
	ofDisableArbTex();
	ofFboSettings* fboSettings = new ofFboSettings();
	fboSettings->width = ofGetWidth();
	fboSettings->height = ofGetHeight();
	fboSettings->textureTarget = GL_TEXTURE_2D;
	fboSettings->internalformat = GL_RGBA32F;
	fboSettings->useDepth = true;
	fboSettings->depthStencilAsTexture = true;
	fboSettings->useStencil = true;
	fboSettings->depthStencilInternalFormat = GL_DEPTH_COMPONENT32F;
	//fboSettings->minFilter = GL_LINEglAR;
	//fboSettings->maxFilter = GL_LINEAR;
	fboSettings->minFilter = GL_NEAREST;
	fboSettings->maxFilter = GL_NEAREST;
	fboSettings->wrapModeHorizontal = GL_CLAMP_TO_EDGE;
	fboSettings->wrapModeVertical = GL_CLAMP_TO_EDGE;
	this->depthFbo.allocate(*fboSettings);
	delete fboSettings;

	camUp = ofVec3f(0.0, 1.0, 0.0);
	camTarget = ofVec3f(0.0, 0.0, 0.0);

	this->lightCam.disableOrtho();
	this->lightCam.setupPerspective();
	lightCam.setNearClip(10.0);
	lightCam.setFarClip(1500.0);


	biasMatrix = ofMatrix4x4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);
	
}


ShadowMap::~ShadowMap()
{
}

void ShadowMap::renderDepthBegin() {
	this->depthFbo.begin();
	depthFbo.clearDepthBuffer(1.0);
}
void ShadowMap::renderDepthEnd() {
	this->depthFbo.end();
}
void ShadowMap::camBegin() {
	this->lightCam.begin();
	moveLight(750.0, 0.5);
	this->lightCam.setPosition(lightPos);
	this->lightCam.lookAt(camTarget, camUp);
}
void ShadowMap::camEnd() {
	this->lightCam.end();
}
void ShadowMap::drawDepthFbo() {
	
	this->depthFbo.draw(0.0, 0.0,
		this->depthFbo.getWidth(), this->depthFbo.getHeight());
}

void ShadowMap::moveLight(float radius, float speed) {
	float t = ofGetFrameNum() * DEG_TO_RAD * speed;
	ofVec3f pos = ofVec3f(radius * sin(t), 500.0, radius * cos(t));
	//speed = 0.0;
	//t = ofGetFrameNum() * DEG_TO_RAD * speed;
	//pos = ofVec3f(radius * sin(t), 300.0, radius * cos(t));
	lightPos = pos;

}
void ShadowMap::drawLight() {
	this->lightCam.drawFrustum();
	ofDrawSphere(lightPos, 50.0);
}

