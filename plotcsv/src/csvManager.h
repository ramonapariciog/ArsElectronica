#ifndef _CSV_MANAGER
#define _CSV_MANAGER
#include "ofMain.h"
#include "ofxCsv.h"

class CsvManager{
	private:
		// File counter
    int countfiles, countnight, playCurrentNight;
		bool reload;
		vector<int> nightsNumbers;
		vector<int> nightsIndices;
		string extract_word();
		int extract_night_number(string filepath);
		void getNights();
		void prepareListCsv();
	public:
		// csv object
		ofxCsv csv;
		// Row counters for the data array
    int totalrows, numcols, currentNight;
		bool nextfile;
		// Stores the file list on csv folder
		vector <ofFile> files;
		string currentfile;
		string currentWord;
		void prepareListFiles(string rootname);
		void chargeFile();
};
#endif
