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
    currentNight = extract_night_number();
    reload = false;
  }
}

string CsvManager::extract_word(){
  vector<string> splitStr = ofSplitString(currentfile, "_");
  return splitStr[1];
}

int CsvManager::extract_night_number(){
  vector<string> splitStr1 = ofSplitString(currentfile, "_");
  vector<string> splitStr2 = ofSplitString(splitStr1[0], "/");
  return ofToInt(splitStr2[2]);
}
