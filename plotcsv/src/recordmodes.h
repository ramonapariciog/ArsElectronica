#ifndef _RECORDMODES
#define _RECORDMODES
#include "ofMain.h"

class RecordModes{
  private:
    vector<int> dreamless;
    vector<int> noEEG;
    vector<int> bothf;
  public:
    void defineMode();
    int whoIs(int night);
    int owner;
};
#endif
