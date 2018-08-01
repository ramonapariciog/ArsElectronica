To install or compile the app in your computer:

 - First download the ofxCsv addon from the creator page: 
     https://github.com/paulvollmer/ofxCsv/tree/master

 - Then copy the both folders: ofxCsv and ofxPlotter (the last one you can find it into the proyect, because was modified to work with different colors), into the "OF/addons" folder.

 - store the csv files inside the plotcsv/bin/data folder
 
 - Last, copy the plotcsv folder into OF/apps/myapps.

 - Create the project with the projectGenerator or Qt, to generate the makefiles, and compile with your favorite ide, or if you want to make it with terminal, move you inside the project folder and apply this command: 
     > make ; make RunRelease

 - have fun
