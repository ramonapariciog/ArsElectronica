#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

int main(){

	//ofSetupOpenGL(1920, 1080, OF_GAME_MODE); // <-------- setup the GL context
        ofSetupOpenGL(1024, 768, OF_GAME_MODE);
	//ofSetupOpenGL(1366, 768, OF_GAME_MODE);
        // this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
