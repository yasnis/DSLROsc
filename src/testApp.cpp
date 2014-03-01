#include "testApp.h"

void testApp::setup() {
	ofXml settings;
	settings.load("../../../SharedData/settings.xml");
	
	ofSetVerticalSync(true);
	ofSetFrameRate(120);
	ofHideCursor();
	ofSetLogLevel(OF_LOG_VERBOSE);
	oscIn.setup(9000);
	oscOut.setup(settings.getValue("osc/camera/address"), 9001);
	capturing = false;
	manual = false;
    
    
    
    photo.init();
    bCamIsBusy = false;
    capturedImage.allocate(1024,1024,OF_IMAGE_COLOR);
    
//	camera.setup();
}

void testApp::update() {
	ofxOscMessage msgIn;
	while(oscIn.getNextMessage(&msgIn)) {
		if(msgIn.getAddress() == "/takePhoto") {
            photo.startCapture();
			capturing = true;
		}
		if(msgIn.getAddress() == "/savePhoto") {
			string filename = msgIn.getArgAsString(0);
            capturedImage.saveImage(filename);
//			camera.savePhoto(filename);
		}
		if(msgIn.getAddress() == "/update") {
//			camera.update();
		}
		if(msgIn.getAddress() == "/setup") {
//			camera.setup();
		}
		if(msgIn.getAddress() == "/createDirectory") {
			string directory = msgIn.getArgAsString(0);
			ofDirectory::createDirectory(directory, true, true);
		}
	}
	
	if(photo.captureSucceeded()) {
        printf("photo.captureSucceeded()");
        pic = photo.capture();
        capturedImage.setFromPixels(pic,photo.getCaptureWidth(),photo.getCaptureHeight(),OF_IMAGE_COLOR,0);
		if(manual) {
//			camera.savePhoto("out.jpg");
            capturedImage.saveImage("out.jpg");
			manual = false;
		} else {
			ofxOscMessage msgOut;
			msgOut.setAddress("/newPhoto");
			oscOut.sendMessage(msgOut);
		}
	}
	
	ofxOscMessage msgOut;
	msgOut.setAddress("/capturing");
	if(!capturing) {
		msgOut.addIntArg(0);
	} else {
		msgOut.addIntArg(1);
	}
	oscOut.sendMessage(msgOut);
}

void testApp::draw() {
	ofBackground(0);
	ofSetColor(255);
	if(!capturing) {
		capturedImage.draw(0, 0);
	}
	ofDrawBitmapStringHighlight("savePath: " + savePath, 10, 20);
	ofDrawBitmapStringHighlight("capturing: " + ofToString(capturing), 10, 40);
}

void testApp::keyPressed(int key) {
	if(key == ' ') {
        photo.startCapture();
		manual = true;
	}
}