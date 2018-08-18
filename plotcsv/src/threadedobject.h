#ifndef THREADEDOBJECT_H
#define THREADEDOBJECT_H

#include "ofThread.h"
#include "ofxCsv.h"
#include "csvManager.h"
#include "arduinoSerial.h"


class MyThread : public ofThread{
    public:
        bool working, comunication;
        CsvManager mycsv;
        ArduinoSerial ars;

        void start(){
            mycsv.prepareListFiles("csvs");
            comunication = ars.startSerial();
            // Load a CSV File.
            mycsv.chargeFile();
            // to wait for the process
            working = false;
            // start the threaded function
            startThread(); //true, false);
        }

        void threadedFunction(){
            while(isThreadRunning()){
              if(comunication){
                while((ars.serial.available()<1) && (!mycsv.nextfile));
                unsigned char val;
                val = ars.read1byte();
                if (val=='S' || val=='N'){
                  mycsv.nextfile = true;
                }
              }
              if(mycsv.nextfile){
                working = true;
                if(lock()){
                  mycsv.chargeFile();
                  unlock();
                  working = false;
                }
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
