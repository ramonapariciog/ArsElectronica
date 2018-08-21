#pragma once

#include "ofMain.h"
#include "threadedobject.h"
// #include "csvManager.h"
#include "ofxPlotter.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed  (int key);
		void exit();

		ofxPlotter plotter;
		ofColor plotCol;

		// Stores the signal names of the eeg array: E0 - E255
		vector <string> names;

		// Selects the total number of signals to plot
		int nchannels;

		// Alpha for fade out
		int alpha;

		// Modifies the word position on screen
		int posx, posy;

		// counter for the rows in csv
		int countrow;

    // time elapsed since loading the csv file
		float startTime;

		// Font style object
		ofTrueTypeFont myfont, infofont;

		// word to plot on screen
    string showedword, showednight;
		string info;

		// Thread object
		MyThread thread;

    // show the night number? and flip the plot falling down/up
		bool showinfo, reverse;

		// settings
		ofxXmlSettings XML;

		// Not used ... For now
		// ----------------------------------------------------
		// void keyReleased(int key);
		// void mouseMoved(int x, int y );
		// void mouseDragged(int x, int y, int button);
		// void mousePressed(int x, int y, int button);
		// void mouseReleased(int x, int y, int button);
		// void windowResized(int w, int h);
		// void dragEvent(ofDragInfo dragInfo);
		// void gotMessage(ofMessage msg);
		// -------------------------------------------------------
};
