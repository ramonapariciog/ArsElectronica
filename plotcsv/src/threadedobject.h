#ifndef THREADEDOBJECT_H
#define THREADEDOBJECT_H

#include "ofThread.h"
#include "ofxCsv.h"
#include "csvManager.h"
#include "arduinoSerial.h"


class MyThread : public ofThread{
    public:
        bool working, comunication, evaluation;
        CsvManager mycsv;
        ArduinoSerial ars;
        ofstream reportFile;

        void start(){
            mycsv.prepareListFiles("csvs");
            comunication = ars.startSerial();
            // Load a CSV File.
            mycsv.chargeFile();
            // to wait for the process
            working = false;
            // flag to evaluate the current word
            evaluation = false;
            // start the threaded function
            startThread(true); //true, false);
        }

        void threadedFunction(){
            string st2filerep;
            string pathReport;
            string dateString;
            string judge;
            pathReport = "reports";
            ofDirectory reportdirs(pathReport);
            if(!reportdirs.doesDirectoryExist(pathReport))
                reportdirs.createDirectory(pathReport);
            dateString = ofGetTimestampString("%Y_%m_%d_%H_%M");
            reportFile.open(ofToDataPath(pathReport + "/report_" + dateString + ".txt" ).c_str() , ios::out);
            while(isThreadRunning()){
              if(comunication){
                while((ars.serial.available()<1) && (!mycsv.nextfile));
                unsigned char val;
                val = ars.read1byte();
                if (val=='S'){
                  judge = "YES";
                }
                if (val=='N'){
                  judge = "NO";
                }
                if (val=='P'){
                  judge = "POSSIBLE";
                }
                st2filerep = judge + ',' + mycsv.currentWord + ',' + ofToString(mycsv.currentNight, 0, 3, '0');
                if(!evaluation){
                  reportFile << st2filerep << "\n";
                  evaluation = true;
                }
              }
              if(mycsv.nextfile){
                if (comunication){
                  evaluation = false;
                }
                working = true;
                if(lock()){
                  mycsv.chargeFile();
                  unlock();
                  working = false;
                }
              }
            }
        }

        void stop(){
          //unlink(ofToDataPath(filename).c_str());
          if(comunication)
            ars.serial.close();
          stopThread();
          reportFile.close();
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
//
// };

#endif // THREADEDOBJECT_H
