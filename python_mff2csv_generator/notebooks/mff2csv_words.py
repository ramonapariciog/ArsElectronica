#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#    _  _   _  ___  _       _       _     _
#  _| || |_/ |/ _ \/ |_ __ (_) __ _| |__ | |_ ___
# |_  ..  _| | | | | | '_ \| |/ _` | '_ \| __/ __|
# |_      _| | |_| | | | | | | (_| | | | | |_\__ \
#   |_||_| |_|\___/|_|_| |_|_|\__, |_| |_|\__|___/
#                             |___/

"""
Load MFF file, and generate CSV files for each trigger.
"""
import os
import sys
import re
import mne
import pandas as pd
import numpy as np
import time
import datetime
import sys
sys.path.append('../src/')
from events_parser import table_night

# inceptions = pd.read_csv('results/inception.csv')
# title  XXX_WWW_YYYY-MM-DD-HH-MM-SS.csv
# XXX being the night number,
# WWW being the word incepted,
# YYYY-MM-DD-HH-MM-SS being the date/hour

def night_number(stringname):
    noche = re.findall(pattern='\d+[a-zA-Z]?', string=stringname)[0]
    numero = re.findall(pattern='\d+', string=noche)[0]
    return numero

if not os.path.exists('../data/results'):
    os.mkdir('../data/results')

if len(sys.argv)>1:
	dir_path = sys.argv[1]
else:
    # dir_path = "../data/raw/EEG"
    dir_path = "/media/quetzal/101NightsEEG"
pattern = r"Nathalie\-\w+\_\d+\_\d+\.mff$"
files = [f for f in os.listdir(dir_path) if re.match(pattern, f)]
print(files)
mne.set_log_level(verbose='CRITICAL')
for f in files:
    print("processing file: ", f)
    fields = re.findall(pattern='\d+', string=f)
    nonight = '{:03d}'.format(int(night_number(f)))
    datehour = time.strftime('%Y-%m-%d-%H-%M-%S',
                             time.strptime('-'.join(fields[1:]),
                                           '%Y%m%d-%H%M%S'))
    path_to_file = os.path.join(dir_path, f)
    try:
        raw = mne.io.read_raw_egi(path_to_file,
                                  montage='GSN-HydroCel-256',
                                  preload=False)
        events = mne.find_events(raw)
        table_words_eeg = table_night(night=int(nonight),
                                      obj={"raw": raw, "events": events})
        print(datetime.datetime.fromtimestamp(raw.info['meas_date'][0]))
        s = [t for t,n,e in events if e==raw.event_id['DIN1']]

        for i,inception in enumerate(s):
            raw = mne.io.read_raw_egi(path_to_file,
                                      montage='GSN-HydroCel-256',
                                      preload=False)
            fs = raw.info['sfreq']
            if inception/fs+55 <= raw.times.max():
                timing = datetime.datetime.fromtimestamp(
                    raw.info['meas_date'][0]+inception/fs)
                timing = timing.strftime("%Y-%m-%d-%H-%M-%S")
                print(f"{i}: {timing} {inception} samples {inception/fs} sec")
                raw.crop(inception/fs-5, inception/fs+55)
                raw.load_data()
                raw.filter(0.15, 50, fir_design='firwin', method='iir')
                raw.set_eeg_reference('average', projection=True)
                # raw.plot()
                chs = mne.pick_types(raw.info, eeg=True)
                data = raw.get_data()[chs,:]
                word = table_words_eeg.loc[i].word
                pathres = "../data/results"
                title = '{0}_{1}_{2}.csv'.format(nonight, word, timing)
                pathres = os.path.join(pathres, title)
                np.savetxt(pathres, data[chs,:].T)
    except Exception as exception:
        typerror = type(exception).__name__
        lineno = exception.__traceback__.tb_lineno
        cause = exception.__str__()
        print(f"{i}: {typerror} in {lineno}, {cause}, {timing} ",
              f"{inception} samples {inception/fs} sec")
