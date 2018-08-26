#include "csvManager.h"

void CsvManager::prepareListFiles(string rootname){
  // report level of the ofxcsv manager
  ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE); // See what's going on inside.
  ofDirectory dir(rootname);
  dir.allowExt("csv");
  dir.listDir();
  dir.sort();
  files = dir.getFiles();
  // Night vector to match csv and wav files
  countnight = 0;
  getNights();
  playCurrentNight = nightsNumbers[countnight];
  prepareListCsv();
  dreamplay.ListWavFiles("audio");
  dreamplay.loadDream(playCurrentNight);
  // Counter files Initialized on zero for the first file on list
  countfiles = 0;
  nextfile = false;
  reload = true;
}

void CsvManager::chargeFile(){
  if (nextfile){
    if (countfiles + 1 < nightsIndices.size()){
      countfiles ++;
      ofLog() << countfiles << " de " << nightsIndices.size();
    }
    else{
      countfiles = 0;
      if (countnight < nightsNumbers.size()){
        if (!dreamplay.isplaying()){
          countnight ++;
          dreamplay.loadDream(playCurrentNight);
          ofLog() << countnight << " de " << nightsNumbers.size();
        }
      }
      else
        countnight = 0;
      playCurrentNight = nightsNumbers[countnight];
      ofLog() << playCurrentNight;
      nightsIndices.clear();
      prepareListCsv();
    }
    reload = true;
    nextfile = false;
  }
  if (reload){
    // current csv file string
    currentfile = files[nightsIndices[countfiles]].path();
    // Load a CSV File.
    csv.load(currentfile,  " ");
    // To know the total number of samples in csv and signals
    totalrows = csv.getNumRows();
    numcols = csv.getNumCols();
    // deactivate the reload flag
    currentWord = extract_word();
    currentNight = extract_night_number(currentfile);
    reload = false;
  }
}

void CsvManager::prepareListCsv(){
  int night;
  for(int i = 0; i < files.size(); i++){
    night = extract_night_number(files[i].path());
    if (night == playCurrentNight){
      nightsIndices.push_back(i);
    }
  }
  std::random_shuffle(nightsIndices.begin(), nightsIndices.end());
  for(int i =0; i < nightsIndices.size(); i++)
    ofLog() << files[nightsIndices[i]].path();
}

void CsvManager::getNights(){
  int night;
  for(int i = 0; i < files.size(); i++)
  {
    night = extract_night_number(files[i].path());
    std::vector<int>::iterator it = std::find(nightsNumbers.begin(), nightsNumbers.end(), night);
    if(it == nightsNumbers.end())
      nightsNumbers.push_back(night);
  }
  std::random_shuffle(nightsNumbers.begin(), nightsNumbers.end());
  for(int i = 0 ; i < nightsNumbers.size(); i++)
    ofLog() << "Enlisted Night: #" << nightsNumbers[i];
}

string CsvManager::extract_word(){
  vector<string> splitStr = ofSplitString(currentfile, "_");
  return splitStr[1];
}

int CsvManager::extract_night_number(string filepath){
  vector<string> splitStr1 = ofSplitString(filepath, "_");
  vector<string> splitStr2 = ofSplitString(splitStr1[0], "/");
  return ofToInt(splitStr2.back());
}
