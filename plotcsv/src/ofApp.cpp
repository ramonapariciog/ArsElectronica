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
  // Aditional positions of the word
  posx = 0;
  posy = 0;
  ofSetFrameRate(30);
  // Seting the font style
  myfont.load("InaiMathi.ttf", 60);
  infofont.load("InaiMathi.ttf", 20);
  //Thread starting
  thread.start();
  // Extracts the word from the current string name file
  showedword = thread.mycsv.currentWord;
  showednight = ofToString(thread.mycsv.currentNight, 0, 3, '0');
  shownight = false;
  reverse = false;
  // countrows
  countrow = 0;
  // Setting the plotter parameters
  //-------------------------------------------------------
  // name for the signal vector
  string name;
  // Starts showing 16 signals but can be increased by 'n' key
  nchannels = 16;
  plotter.setWindowSize(500);
  for(int ix=0; ix < thread.mycsv.numcols; ix++){
      name = "E" + ofToString(ix,0,3,'0');
      names.push_back(name);
  }
  // ------------------------------------------------------
}

//--------------------------------------------------------------
void ofApp::update(){
  int fframes = 6;
  // ofFill();
  if (!thread.working){
    thread.mycsv.dreamplay.playDream();
    if (alpha < 255)
      alpha = alpha + fframes;
    else
      alpha = 255;
    // there is not load process currently
    showedword = thread.mycsv.currentWord;
    showednight = ofToString(thread.mycsv.currentNight, 0, 3, '0');
    int xcount = 7;
    for(int i = countrow*xcount; i < (countrow+1)*xcount; i++)
    {
      for(int j = 0; j < nchannels; j++) {
         plotter[names[j]] << ofToFloat(thread.mycsv.csv[i][j]) * 10000;
      }
    }
    if (countrow * xcount <= (thread.mycsv.totalrows-(2*xcount))){
      countrow ++;
    }
    else{
      countrow = 0;
      alpha = 255;
      thread.mycsv.nextfile = true;
    }
  }
  else{
   //  Animation for the transition time
    if (alpha > fframes)
      alpha = alpha - fframes;
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(0);
  ofBackgroundGradient(ofColor(0), ofColor(0));
  if(!reverse){
    ofRotateZ(90);
    ofTranslate(-65, -ofGetWidth());
    // plotter.updateHistory();
    plotter.draw(0, 0, ofGetHeight() + 140, ofGetWidth());
    // Fade in/out sequence
    // ---------------------------------------------------
    ofSetColor( 0, 0, 0, 255 - alpha );
    ofFill();
    ofRect( 0, 0,  ofGetHeight() + 140, ofGetWidth());
    plotCol = ofColor::fromHsb(0, 0, 255, alpha);
    ofSetColor(plotCol);
    ofRotateZ(-90);
    ofTranslate(-(ofGetWidth()/2) + posx, ofGetHeight()/4 + 100 + posy);
  }
  else{
    ofRotateZ(-90);
    ofTranslate(-ofGetHeight()-65, 0);
    // plotter.updateHistory();
    plotter.draw(0, 0, ofGetHeight() + 140, ofGetWidth());
    // Fade in/out sequence
    // ---------------------------------------------------
    ofSetColor( 0, 0, 0, 255 - alpha );
    ofFill();
    ofRect( 0, 0,  ofGetHeight() + 140, ofGetWidth());
    plotCol = ofColor::fromHsb(0, 0, 255, alpha);
    // ---------------------------------------------------
    ofSetColor(plotCol);
    ofRotateZ(90);
    ofTranslate((ofGetWidth()/2) + posx, -ofGetWidth()/2 + 100 + posy);
  }
  glScalef(1.0, -1.0, 1.0);
  myfont.drawString(showedword, -myfont.stringWidth(showedword)/2, 0);
  if (shownight){
    glScalef(1.0, -1.0, 1.0);
    infofont.drawString(showednight, -infofont.stringWidth(showednight)/2, 200);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == 's')
      nchannels = nchannels + 8;
  if (key == OF_KEY_RIGHT)
      posx = posx + 10;
  if (key == OF_KEY_UP)
      posy = posy + 10;
  if (key == OF_KEY_LEFT)
      posx = posx - 10;
  if (key == OF_KEY_DOWN)
      posy = posy - 10;
  if (key == 'i'){
    // To show the night number in screen
    if (shownight)
      shownight = false;
    else
      shownight = true;
  }
  if (key == 'r'){
    // to revert the direction of the lines
    if (reverse)
      reverse = false;
    else
      reverse = true;
  }
  if (key == 'n'){
    // To change the word_scene
    alpha = 255;
    thread.mycsv.nextfile = true;
  }
  ofLog() << "posx" << posx << "posy" << posy;
}

// //--------------------------------------------------------------
// void ofApp::keyReleased(int key){
// }
//
// //--------------------------------------------------------------
// void ofApp::mouseMoved(int x, int y ){
// }
//
// //--------------------------------------------------------------
// void ofApp::mouseDragged(int x, int y, int button){
// }
//
// //--------------------------------------------------------------
// void ofApp::mousePressed(int x, int y, int button){
// }
//
// //--------------------------------------------------------------
// void ofApp::mouseReleased(int x, int y, int button){
// }
//
// //--------------------------------------------------------------
// void ofApp::windowResized(int w, int h){
// }
//
// //--------------------------------------------------------------
// void ofApp::gotMessage(ofMessage msg){
// }
//
// //--------------------------------------------------------------
// void ofApp::dragEvent(ofDragInfo dragInfo){
// }
