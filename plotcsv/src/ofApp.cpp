
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  // Aditional positions of the word
  if(XML.loadFile("Settings.xml") ){
		ofLog() << "Settings.xml loaded!";
	}else{
		ofLog() << "unable to load mySettings.xml check data/ folder";
	}
  posx = XML.getValue("SETTINGS:POSITIONSTRING:POSX", 0);
  posy = XML.getValue("SETTINGS:POSITIONSTRING:POSY", 0);
  flipv = XML.getValue("SETTINGS:FLIPVER:VERT", 1);
  fliph = XML.getValue("SETTINGS:FLIPHOR:HORZ", 1);
  track = XML.getValue("SETTINGS:TRACKSCREEN:TRACKX", 0);
  ofSetFrameRate(30);
  // Seting the font style
  myfont.load("InaiMathi.ttf", 60);
  infofont.load("Big Bubu.ttf", 20);
  //Thread starting
  thread.start();
  // Extracts the word from the current string name file
  showedword = thread.mycsv.currentWord;
  showednight = ofToString(thread.mycsv.currentNight, 0, 3, '0');
  showinfo = false;
  reverse = XML.getValue("SETTINGS:DIRECTION:REVERSE", true);
  // countrows
  countrow = 0;
  // Setting the plotter parameters
  //-------------------------------------------------------
  // name for the signal vector
  string name;
  // Starts showing 16 signals but can be increased by 'n' key
  nchannels = XML.getValue("SETTINGS:CHANNELS:NCHANNELS", 16);
  plotter.setWindowSize(500);
  for(int ix=0; ix < thread.mycsv.numcols; ix++){
      name = "E" + ofToString(ix,0,3,'0');
      names.push_back(name);
  }
  // ------------------------------------------------------
  startTime = ofGetElapsedTimef();
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
    int xcount = 4;
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
    startTime = ofGetElapsedTimef();
    if (alpha > fframes)
      alpha = alpha - fframes;
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(0);
  ofBackgroundGradient(ofColor(0), ofColor(0));
  if(!reverse){
    ofRotate(track, 0.1, 0, 0);
    ofRotateZ(90);
    ofTranslate(-65, -ofGetWidth());
    // plotter.updateHistory();
    if (thread.mycsv.mode != 2)
    {
      plotter.draw(0, 0, ofGetHeight()*2 + 140, ofGetWidth());
    }
    else
    {
      if (!thread.working)
        alpha = 0;
    }

    // Fade in/out sequence
    // ---------------------------------------------------
    ofSetColor( 0, 0, 0, 255 - alpha );
    ofFill();
    ofRect( 0, 0,  ofGetHeight()*2 + 140, ofGetWidth());
    plotCol = ofColor::fromHsb(0, 0, 255, alpha);
    ofSetColor(plotCol);
    ofRotateZ(-90);
    ofTranslate(-(ofGetWidth()/2) + posx, ofGetHeight()/4 + 100 + posy);
  }
  else{
    ofRotate(track, 0.1, 0, 0);
    ofRotateZ(-90);
    ofTranslate(-ofGetHeight()-65, 0);
    // plotter.updateHistory();
    if (thread.mycsv.mode != 2)
    {
      plotter.draw(0, 0, ofGetHeight()*2 + 140, ofGetWidth());
    }
    else
    {
      if (!thread.working)
        alpha = 0;
    }
    // Fade in/out sequence
    // ---------------------------------------------------
    ofSetColor( 0, 0, 0, 255 - alpha );
    ofFill();
    ofRect( 0, 0,  ofGetHeight()*2 + 140, ofGetWidth());
    plotCol = ofColor::fromHsb(0, 0, 255, alpha);
    // ---------------------------------------------------
    ofSetColor(plotCol);
    ofRotateZ(90);
    ofTranslate((ofGetWidth()/2) + posx, -ofGetWidth()/2 + 100 + posy);
  }
  int timeelapsed = (int)(ofGetElapsedTimef()-startTime);
  if (showinfo){
    info = "Night " + ofToString(showednight);
    info = info + ", mode: " + ofToString(thread.mycsv.mode);
    info = info + ", posx: " + ofToString(posx);
    info = info + ", posy: " + ofToString(posy);
    info = info + ", n.channels: " + ofToString(nchannels);
    info = info + ", Xtrack: " + ofToString(track);
    info = info + ", time: " + ofToString(timeelapsed);
    ofSetColor(255, 120, 120, 255);
    infofont.drawString(info, -infofont.stringWidth(info)/2, 200);
  }
  glScalef(fliph, flipv, 1.0);
  ofSetColor(plotCol);
  if (thread.mycsv.mode != 2)
    myfont.drawString(showedword, -myfont.stringWidth(showedword)/2, 0);
  if (timeelapsed > 65)
    thread.mycsv.nextfile = true;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == 's')
      nchannels = nchannels + 8;
  if (key == 'd')
      nchannels = nchannels - 8;
  if (key == OF_KEY_RIGHT)
      posx = posx + 10;
  if (key == OF_KEY_UP)
      posy = posy + 10;
  if (key == OF_KEY_LEFT)
      posx = posx - 10;
  if (key == OF_KEY_DOWN)
      posy = posy - 10;
  if (key == 'i'){
    // To show the info in screen
    if (showinfo)
      showinfo = false;
    else
      showinfo = true;
  }
  if (key == 'r'){
    // to revert the direction of the lines
    if (reverse)
      reverse = false;
    else
      reverse = true;
  }
  if (key == 'u')
    track = track + 5;
  if (key == 'm')
    track = track - 5;
  if (key == 'f'){
    if (flipv == 1)
      flipv = -1;
    else
      flipv = 1;
  }
  if (key == 'h'){
    if (fliph == 1)
      fliph = -1;
    else
      fliph = 1;
  }
  if (key == 'n'){
    // To change the word_scene
    alpha = 255;
    thread.mycsv.nextfile = true;
  }
}

void ofApp::exit(){
  XML.setValue("SETTINGS:POSITIONSTRING:POSX", posx);
  XML.setValue("SETTINGS:POSITIONSTRING:POSY", posy);
  XML.setValue("SETTINGS:DIRECTION:REVERSE", reverse);
  XML.setValue("SETTINGS:CHANNELS:NCHANNELS", nchannels);
  XML.setValue("SETTINGS:TRACKSCREEN:TRACKX", track);
  XML.setValue("SETTINGS:FLIPVER:VERT", flipv);
  XML.setValue("SETTINGS:FLIPHOR:HORZ", fliph);
  XML.saveFile("Settings.xml");
  thread.stop();
  ofLog() << "saliendo";
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
