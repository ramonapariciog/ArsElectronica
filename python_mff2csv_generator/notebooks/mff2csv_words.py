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
import json
sys.path.append('../src/')
from events_parser import table_night
from logtofile import CreateLogger

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

selected_night = None
if len(sys.argv) == 2:
	dir_path = sys.argv[1]
elif len(sys.argv) > 2:
    dir_path = sys.argv[1]
    selected_night = int(sys.argv[2])
else:
    dir_path = "/media/quetzal/101NightsEEG"
    # dir_path = "../data/raw/EEG"

trad_dictionary = json.load(open('words2translate.json', 'r'))
errors = CreateLogger("errorsDreams")
bad_register_night = []
total_words = np.empty((0, ))
pattern = r"Nathalie\-\w+\_\d+\_\d+\.mff$"
files = [f for f in os.listdir(dir_path) if re.match(pattern, f)]
mne.set_log_level(verbose='CRITICAL')
for f in files:
    fields = re.findall(pattern='\d+', string=f)
    nonight = '{:03d}'.format(int(night_number(f)))
    if selected_night is not None:
        if int(night_number(f)) != selected_night:
            continue
    print("processing file: ", f)
    print("Night number: ", int(night_number(f)))
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
        total_words = np.hstack(tup=(total_words, table_words_eeg.word.values))
        print(table_words_eeg.word.values)
        print(datetime.datetime.fromtimestamp(raw.info['meas_date'][0]))
        s = [t for t, n, e in events if e == raw.event_id['DIN1']]
        for i, inception in enumerate(s):
            raw = mne.io.read_raw_egi(path_to_file,
                                      montage='GSN-HydroCel-256',
                                      preload=False)
            fs = raw.info['sfreq']
            if inception / fs + 55 <= raw.times.max():
                timing = datetime.datetime.fromtimestamp(
                    raw.info['meas_date'][0] + inception / fs)
                timing = timing.strftime("%Y-%m-%d-%H-%M-%S")
                print(f"{i}: {timing} {inception} samples {inception/fs} sec")
                raw.crop(inception / fs - 5, inception / fs + 55)
                raw.load_data()
                raw.filter(0.15, 50, fir_design='firwin', method='iir')
                raw.set_eeg_reference('average', projection=True)
                chs = mne.pick_types(raw.info, eeg=True)
                data = raw.get_data()[chs, :]
                word = table_words_eeg.iloc[i].word
                word = trad_dictionary.get(word, word)
                pathres = "../data/results"
                title = '{0}_{1}_{2}.csv'.format(nonight, word, timing)
                pathres = os.path.join(pathres, title)
                np.savetxt(pathres, data[chs, :].T)
    except Exception as exception:
        typerror = type(exception).__name__
        lineno = exception.__traceback__.tb_lineno
        cause = exception.__str__()
        errors.logger.info(f"{i} {nonight} {f}: {inception} {word} {timing}")
        errors.logger.exception(exception)
        bad_register_night.append(nonight)
        print(f"\nError\n{f}: {typerror} in {lineno}, {cause}")
        # print(f"\nError\n{i}: {typerror} in {lineno}, {cause}, {timing} ",
        #       f"{inception} samples {inception/fs} sec\n")
