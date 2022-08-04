#!/usr/bin/python


import tkinter as tk
from random import randint
from tkinter import *
from lakeshore import Teslameter

top = tk.Tk()

color1 = ["blue","red","green","black"]
j = 0

def changeColor():
    i = randint(0,3)
    B.itemconfigure(oval, fill = color1[i])
    B.after(1000, changeColor)
        

def setMagicNumber():
    global j
    j = j+1
    C.configure(text = f'the magic number is {j}')

A= tk.Button(top, text ="Set calibration level", command = setMagicNumber, padx= 20, pady = 20)
A.pack()

C = tk.Label(top, bg = "white", text=f'the magic number is {j}')
C.pack()

B = tk.Canvas(top, bg="white", height=400, width=400)
oval = B.create_oval(50, 50 ,350 , 350, fill=color1[0])
B.pack()

D= tk.Button(top, text ="Change Color!", command = changeColor, padx= 20, pady = 20)
D.pack()
top.mainloop()