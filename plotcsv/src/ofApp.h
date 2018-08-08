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
 *  @modified           2016.04.21
 *  @version            0.2.0
 */

#pragma once

#include "ofMain.h"
#include "threadedobject.h"
// #include "csvManager.h"
#include "ofxPlotter.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed  (int key);

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

		bool charging;

		// Font style object
		ofTrueTypeFont myfont;

		// word to plot on screen
    string showedword;

		// Thread object
		MyThread thread;

		// // Flag to control the csv transition
		// bool nextfile;

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
