#pragma once

#include "ofMain.h"

//#include "ofxEdsdk.h"
#include "ofxOsc.h"
#include "ofxPhoto.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	
//	ofxEdsdk::Camera camera;
	ofxOscReceiver oscIn;
	ofxOscSender oscOut;
	
	string savePath;
	bool capturing;
	bool manual;
    
    
    ofxPhoto photo;
    bool bCamIsBusy;
    
    ofImage capturedImage;
    
    unsigned char *pic;
};
