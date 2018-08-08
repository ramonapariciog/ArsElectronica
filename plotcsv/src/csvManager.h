#ifndef _CSV_MANAGER
#define _CSV_MANAGER
#include "ofMain.h"
#include "ofxCsv.h"

class CsvManager{
	private:
		// File counter
    int countfiles;
		bool reload;
	public:
		void prepareListFiles(string rootname);
		void chargeFile();
		string extract_word();
		// csv object
		ofxCsv csv;
		// Row counters for the data array
    int totalrows, numcols;
		bool nextfile;
		// Stores the file list on csv folder
		vector <ofFile> files;
		string currentfile;
		string currentWord;
};
#endif
