#include "ofApp.h"

	
//--------------------------------------------------------------
void ofApp::setup(){
    
	ofSetVerticalSync(true);
    server.setup(10002);
    
    server.setMessageDelimiter("\n");

	tubeResolution.addListener(this, &ofApp::tubeResolutionChanged);
	ringButton.addListener(this,&ofApp::ringButtonPressed);

	gui.setup();
	gui.add(filled.setup("fill", false));
	gui.add(radius.setup( "radius", 140, 10, 300 ));
	gui.add(color.setup("color",ofColor(15,100,150),ofColor(0,0),ofColor(255,255)));
	gui.add(tubeResolution.setup("tube res", 30, 3, 50));
	gui.add(ringButton.setup("ring"));
    gui.add(rotation.setup("rotation", 1, -1, 1));

	bHide = true;

	ring.loadSound("ring.wav");
    
    cylinder.set(radius, 250);
     cylinder.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    cylinder.rotate(90, 10, 0, 0);
}

//--------------------------------------------------------------
void ofApp::exit(){
	ringButton.removeListener(this,&ofApp::ringButtonPressed);
}

//--------------------------------------------------------------
void ofApp::tubeResolutionChanged(int & tubeResolution){
	cylinder.setResolution(tubeResolution, (int)tubeResolution/2,(int)tubeResolution/4);
}

//--------------------------------------------------------------
void ofApp::ringButtonPressed(){
	ring.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	cylinder.setResolution(tubeResolution, (int)tubeResolution/2, (int)tubeResolution/4);
    
    for(int i = 0; i < server.getLastID(); i++){
        if( !server.isClientConnected(i) )continue;
        
        server.send(i, "hi. you're connected on port:"+ofToString(server.getClientPort(i))+"\n"+ofToString((int)(radius)));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    cam.begin();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    
    cylinder.rotate(rotation,0,0,1);
    
    ofBackground(ofColor::lightGray);
    ofSetColor(color);
    ofNoFill();
    
    cylinder.set(radius, 250);
   
    
	if( filled ){
        cylinder.draw();
		ofFill();
        ofSetColor(0, 25);
        cylinder.drawWireframe();
 
	}else{
        ofSetColor(0,0,0,0);
        cylinder.draw();
        ofSetColor(color);
        cylinder.drawWireframe();
	}
    cam.end();
    ofPopMatrix();
    
    
    if( bHide ){
        gui.draw();
        ofSetColor(ofColor::black);
        ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate()), 15, ofGetHeight()-20);
        ofDrawBitmapString("Server Test\nPort:"+ofToString(server.getPort())+"\nConnected: "+ofToString(server.getLastID()), 15, ofGetHeight()-80);
    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( key == 'h' ){
		bHide = !bHide;
	}
	if(key == 's') {
		gui.saveToFile("settings.xml");
	}
	if(key == 'l') {
		gui.loadFromFile("settings.xml");
	}
	if(key == ' '){
		color = ofColor(255);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
