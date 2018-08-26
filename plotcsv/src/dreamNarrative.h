#ifndef _DREAM_NARRATIVE
#define _DREAM_NARRATIVE
#include "ofMain.h"

class DreamNarrative{
  private:
    int extract_night_number(string filepath);
    vector <ofFile> files;
    ofSoundPlayer dream;
  public:
    void ListWavFiles(string rootname);
    void loadDream(int nightnumber);
    void playDream();
    bool isplaying();
    bool played;
};
#endif
