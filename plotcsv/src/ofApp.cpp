/**
 *  ofxCsv
 *  Inspired and based on Ben Fry's [table class](http://benfry.com/writing/map/Table.pde)
 *
 *  The MIT License
 *
 *  Copyright (c) 2011-2014 Paul Vollmer, http://www.wng.cc
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *
 *  @modified           2016.04.23
 *  @version            0.2.0
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    string name;
    nextfile = false;
    countrow = 0;
    countcol = 0;
    posx = 0;
    posy = 0;
	ofSetFrameRate(30);
	ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE); // See what's going on inside.
    myfont.load("Big Bubu.ttf", 60);
    string path = "csvs";
    ofDirectory dir(path);
    dir.allowExt("csv");
    dir.listDir();
    dir.sort();
    files = dir.getFiles();
    countfiles = 0;

	// Load a CSV File.
    if(csv.load(files[countfiles].path(),  " ")) {
        //csv.trim(); // Trim leading/trailing whitespace from non-quoted fields.
        // Like with C++ vectors, the index operator is a quick way to grab row
        // & col data, however this will cause a crash if the row or col doesn't
        // exist, ie. the file didn't load.
        ofLog() << "Print out a specific CSV value";
        ofLog() << csv[0][1];
        // also you can write...
        // or you can get the row itself...
  	}
    totalrows = csv.getNumRows();
    plotter.setWindowSize(500);
    for(int ix=0; ix<csv.getNumCols(); ix++){
        name = "signal" + ofToString(ix,0,3,'0');
        names.push_back(name);
    }
    nchannels = 16;
    
    string namefileString = files[countfiles].path();
    vector<string> splitString = ofSplitString(namefileString, "_");
    showedword = splitString[1];
}

//--------------------------------------------------------------
void ofApp::update(){
    if (nextfile){
        countfiles ++;
        csv.load(files[countfiles].path(), " ");
        ofLog() << files[countfiles].path();
        nextfile = false;
        string namefileString = files[countfiles].path();
        vector<string> splitString = ofSplitString(namefileString, "_");
        showedword = splitString[1];
    }
    ofFill();
    int xcount = 2;
    if (countrow * xcount <= (totalrows-2*xcount)){
        countrow ++;
    }
    else{
        countrow = 0;
    }

    for(int i = countrow*xcount; i < (countrow+1)*xcount; i++) {
        for(int j = 0; j < nchannels; j++) {
           plotter[names[j]] << ofToFloat(csv[i][j]) * 10000;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);
    ofBackgroundGradient(ofColor(0), ofColor(0));
    ofRotateZ(-90);
    ofTranslate(-ofGetHeight()-65, 0);
    //ofRotateY(40);
    plotter.draw(0, 0, ofGetHeight() + 140, ofGetWidth());
    ofColor plotCol = ofColor::fromHsb(0, 0, 255, 255);
    ofSetColor(plotCol);
    ofRotateZ(90);
    //ofRotateX(-90);
    ofTranslate(ofGetHeight()/2 + 400 + posx,-ofGetWidth()/2 + 100 + posy);//ofGetHeight()*2, 0);
    glScalef(-1.0, 1.0, 1.0);
    myfont.drawString(showedword, 0, 0);//ofGetWidth()/2, ofGetWidth()/2);
    //ofDrawBitmapString("Hola", ofGetWidth()/2, ofGetWidth()/2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's')
        nchannels = nchannels + 8;
    if (key == 'g')
        nchannels = nchannels - 5;
    if (key == 'd')
        posx = posx + 100;
    if (key == 'z')
        posy = posy + 100;
    if (key == 'q')
        posx = posx - 100;
    if (key == 'x')
        posy = posy - 100;
    //Para cambiar entre archivos
    if (key == 'n')
        nextfile = true;
    ofLog() << "posx" << posx << "posy" << posy;
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
