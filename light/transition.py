#  -*- coding: utf8 -*-

import colorsys
import time

import serial

ser = serial.Serial("/dev/ttyACM0", timeout=1)

def val_interm(hsl1, hsl2, pos):
	""" Valeur intermédiaire entre la couleur 1 et la couleur 2
	pos correspond à la postion dans la transition, entre 0 (couleur 1) et 1 (couleur2)
	"""
	res_h = (hsl2[0]-hsl1[0])*pos + hsl1[0]

	res_l = abs(hsl2[2]-hsl1[2])*pos + hsl1[2]
	res_s = abs(hsl2[1]-hsl1[1])*pos + hsl1[1]
	r, g, b = colorsys.hls_to_rgb(res_h, res_l, res_s)

	print "pos : ", pos, "   orig : ", hsl1, "  | dest : ", hsl2
	print "hls : ", "{}, {}, {}".format(res_h,  res_l, res_s)
	print "rgb : ", "{}, {}, {}".format(r, g, b)

	return r, g, b

def correction(col):
	print "rgb avant : ", col
	cor = [255, 212.0, 221.0]
	res = [int(val * c) for val, c in zip(col, cor)]
	print "rgb : ", res
	return res

color1_hsl = (240.0/360.0, 100.0/100.0,  0.0/100.0) # black blue
color2_hsl = (240.0/360.0, 100.0/100.0, 40.0/100.0) # blue
color3_hsl = (360.0/360.0, 100.0/100.0, 40.0/100.0) # red
color4_hsl = (56.0/360.0,  100.0/100.0, 50.0/100.0)
color5_hsl = (360.0/360.0, 100.0/100.0, 100.0/100.0) # white 

transition1 = {"orig": color1_hsl, "end": color2_hsl, "dur": 100}
transition2 = {"orig": color2_hsl, "end": color3_hsl, "dur": 100}
transition3 = {"orig": color3_hsl, "end": color4_hsl, "dur": 100}
transition4 = {"orig": color4_hsl, "end": color5_hsl, "dur": 100}

sleep_time = 1

# for t in range(1, transition1["dur"]+1):
# 	res = val_interm(transition1["orig"], transition1["end"], t*1.0/transition1["dur"])
# 	res = correction(res)
# 	ser.write(",".join(map(str, res))+"\n")
# 	ser.readline().strip()
# 	ser.readline()
# 	time.sleep(1)

# for t in range(1, transition2["dur"]+1):
# 	res = val_interm(transition2["orig"], transition2["end"], t*1.0/transition1["dur"])
# 	res = correction(res)
# 	ser.write(",".join(map(str, res))+"\n")
# 	ser.readline().strip()
# 	ser.readline()
# 	time.sleep(1)

for t in range(1, transition3["dur"]+1):
	res = val_interm(transition3["orig"], transition3["end"], t*1.0/transition1["dur"])
	res = correction(res)
	ser.write(",".join(map(str, res))+"\n")
	ser.readline().strip()
	ser.readline()
	time.sleep(1)

for t in range(1, transition4["dur"]+1):
	res = val_interm(transition4["orig"], transition4["end"], t*1.0/transition1["dur"])
	res = correction(res)
	ser.write(",".join(map(str, res))+"\n")
	ser.readline().strip()
	ser.readline()
	time.sleep(1)