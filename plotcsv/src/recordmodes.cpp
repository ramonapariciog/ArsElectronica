#include "recordmodes.h"
// dreamless:
void RecordModes::defineMode(){
  dreamless = {1, 2, 4, 5, 6, 13, 18, 25, 26, 27, 29, 38, 44, 47, 48,
               56, 71, 76, 92};
  noEEG = {9, 14, 28, 88, 98, 68, 51, 37};
  bothf = {3, 7, 8, 10, 11, 12, 15, 16, 17, 19, 20, 21, 22, 23, 24,
           30, 31, 32, 33, 34, 35, 36, 39, 40, 41, 42, 43, 45, 46,
           49, 50, 52, 53, 54, 55, 57, 58, 59, 60, 61, 62, 63, 64,
           65, 66, 67, 69, 70, 72, 73, 74, 75, 77, 78, 79, 80, 81,
           82, 83, 84, 85, 86, 87, 89, 90, 91, 93, 94, 95, 96, 97,
           99, 100, 101};
}
int RecordModes::whoIs(int night){
  // is dreamless
  if(std::find(dreamless.begin(), dreamless.end(), night) != dreamless.end())
  {
    owner = 1;
  }
  // without EEG
  else if (std::find(noEEG.begin(), noEEG.end(), night) != noEEG.end())
  {
    owner = 2;
  }
  // with both functions: EEG + audio
  else if (std::find(bothf.begin(), bothf.end(), night) != bothf.end())
  {
    owner = 3;
  }
  return owner;
}
