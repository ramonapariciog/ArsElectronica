#ifndef THREADEDOBJECT_H
#define THREADEDOBJECT_H

#include "ofThread.h"
#include "ofxCsv.h"
#include "csvManager.h"


class MyThread : public ofThread{
    public:
        bool working;
        CsvManager mycsv;

        void start(){
            mycsv.prepareListFiles("csvs");
            // Load a CSV File.
            mycsv.chargeFile();
            // to wait for the process
            working = false;
            // start the threaded function
            startThread(true, false);
        }

        void threadedFunction(){
            while(isThreadRunning()){
                if(mycsv.nextfile){
                   if(lock())
                      working = true;
                      mycsv.chargeFile();
                      unlock();
                      working = false;
                }
            }
        }
    };
//
//         void draw(){
//             if (playsound)
//             {
//                 lstd.play();
//                 playsound=false;
//             }
//         }
//
//         void stop(){
//             //unlink(ofToDataPath(filename).c_str());
//             stopThread();
//             reportFile.close();
//         }
//
// };

#endif // THREADEDOBJECT_H
