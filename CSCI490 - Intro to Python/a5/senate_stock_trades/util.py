#!/usr/bin/python

import json
import os


data = 0

def get_data():
    global data
    if data == 0:   
        fname = os.path.join(os.path.dirname(__file__),'senate-stock-trades.json')
        with open(fname) as f:
            data = json.load(f)
    return data

def add_ammount_ranges(a,b,c,d):
    new_min = a + c
    if b == None or d == None:
        new_max = None
    else:
        new_max = b + d
    
    return new_min, new_max

def sub_ammount_ranges(a,b,c,d):
    new_min = a - c
    if b == None or d == None:
        new_max = None
    else:
        new_max = b - d
    
    return new_min, new_max