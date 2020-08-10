#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLWindowSettings s;
	s.setGLVersion(4, 6);
	s.setSize(1024, 768);
	ofCreateWindow(s);
	ofRunApp(new ofApp());

}
