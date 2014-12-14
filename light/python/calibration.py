# -*- coding: utf8 -*-

from Tkinter import Tk, Scale, HORIZONTAL, mainloop
import serial

ser = serial.Serial("/dev/ttyACM0", timeout=1)

def send_values(_):
	vr, vg, vb = r.get(), g.get(), b.get()
	res = "{},{},{}".format(vr, vg*212.0/255.0, vb*164.0/255.0)
	print res
	ser.write(res+'\n')
	ard = ser.readline()
	print ard
	ard = ser.readline()
	print ard

master = Tk()
r = Scale(master, from_=0, to=255, length=250, 
		  orient=HORIZONTAL, label="red",
		  command=send_values)
r.pack()
g = Scale(master, from_=0, to=255, length=250, 
		  orient=HORIZONTAL, label="green",
		  command=send_values)
g.pack()
b = Scale(master, from_=0, to=255, length=250, 
		  orient=HORIZONTAL, label="blue",
		  command=send_values)
b.pack()
master.geometry('{}x{}'.format(300, 200))

print r.get()


mainloop()
