#pragma once
#include "ofMain.h"
ofMatrix4x4 getViewMatrix(ofVec3f eye, ofVec3f up, ofVec3f center);
ofMatrix4x4 getProjMatrix(float fov, float aspect, float n, float f);