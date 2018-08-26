#include "dreamNarrative.h"

void DreamNarrative::ListWavFiles(string rootname){
  ofDirectory dir(rootname);
  dir.allowExt("wav");
  dir.listDir();
  dir.sort();
  files = dir.getFiles();
}

void DreamNarrative::loadDream(int nightnumber){
  int night;
  if(!dream.isPlaying()){
    for(int i = 0; i < files.size(); i++){
      night = extract_night_number(files[i].path());
      if(night == nightnumber){
        dream.load(files[i].path());
        dream.setMultiPlay(false);
        played = false;
        break;
      }
    }
  }
}

void DreamNarrative::playDream(){
  if(!dream.isPlaying() && !played){
    dream.play();
    played = true;
  }
}

bool DreamNarrative::isplaying(){
  return dream.isPlaying();
}

int DreamNarrative::extract_night_number(string filepath){
  vector<string> splitStr1 = ofSplitString(filepath, " ");
  vector<string> splitStr2 = ofSplitString(splitStr1[0], "/");
  return ofToInt(splitStr2.back());
}
