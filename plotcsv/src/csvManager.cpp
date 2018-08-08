#include "csvManager.h"

void CsvManager::prepareListFiles(string rootname){
  // report level of the ofxcsv manager
  ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE); // See what's going on inside.
  ofDirectory dir(rootname);
  dir.allowExt("csv");
  dir.listDir();
  dir.sort();
  files = dir.getFiles();
  // Counter files Initialized on zero for the firs file on list
  countfiles = 0;
  nextfile = false;
  reload = true;
}

void CsvManager::chargeFile(){
  if (nextfile){
    countfiles ++;
    reload = true;
    nextfile = false;
  }
  if (reload){
    // current csv file string
    currentfile = files[countfiles].path();
    // Load a CSV File.
    csv.load(currentfile,  " ");
    // To know the total number of samples in csv and signals
    totalrows = csv.getNumRows();
    numcols = csv.getNumCols();
    // deactivate the reload flag
    currentWord = extract_word();
    reload = false;
  }
}

string CsvManager::extract_word(){
  vector<string> splitString = ofSplitString(currentfile, "_");
  return splitString[1];
}
