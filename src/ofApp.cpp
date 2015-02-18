#include "ofApp.h"

	
//--------------------------------------------------------------
void ofApp::setup(){
    
	ofSetVerticalSync(true);
    server.setup(8002);

	// we add this listener before setting up so the initial circle resolution is correct
	tubeResolution.addListener(this, &ofApp::tubeResolutionChanged);
	ringButton.addListener(this,&ofApp::ringButtonPressed);

	gui.setup(); // most of the time you don't need a name
	gui.add(filled.setup("fill", false));
	gui.add(radius.setup( "radius", 140, 10, 300 ));
	gui.add(color.setup("color",ofColor(15,100,150),ofColor(0,0),ofColor(255,255)));
	gui.add(tubeResolution.setup("tube res", 15, 3, 50));
	gui.add(ringButton.setup("ring"));
	gui.add(screenSize.setup("screen size", ""));
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
    screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
