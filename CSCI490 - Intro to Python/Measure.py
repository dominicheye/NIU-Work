#!/usr/bin/python

import tkinter as tk
from tkinter import *
from lakeshore import Teslameter

filename = 'PN_F41'
offset = 0

def set_PN():
    global filename
    PN = B.get()
    filename = f'{PN}_F41'
    D.configure(text = f'Saving as {filename}')

def change_offset():
    global offset
    offset = int(F.get())
    G.configure(text=f'the offset is {offset}')

my_teslameter = Teslameter()
my_teslameter.command('SENSE:MODE DC')
probe_serial_number = my_teslameter.query('PROBE:SNUMBER?')

top = tk.Tk()

A = tk.Label(top, text= 'Enter Part Number here and click ENTER P/N')
A.grid(row = 0, column = 0)

B = tk.Entry(top, bd = 5)
B.grid(row = 0, column = 1)

C = tk.Button(top, text = 'ENTER P/N', command = set_PN)
C.grid(row = 1, column = 0)

D = tk.Label(top, text = f'Saving as {filename}')
D.grid(row = 1, column = 1)

E = tk.Label(top, bg = "white", text=f'Offset Value')
E.grid(row = 0, column=0)

base = StringVar(top, value='0')
F = tk.Entry(top, bd = 5, textvariable=base)
F.grid(row = 0, column=1)

G = tk.Label(top, bg = "white", text=f'the offset is {offset}')
G.grid(row = 1, column=1)