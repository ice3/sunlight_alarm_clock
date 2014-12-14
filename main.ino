#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
 
#define SLEEP_TIME 1000.0     // make this higher to slow down

#define DUR_TRANS1 200.0
#define DUR_TRANS2 250.0
#define DUR_TRANS3 200.0
#define DUR_TRANS4 150.0

#include "Color.h"
#include <DS1302.h>

// Init the DS1302
//         RST, DATA, CLK
DS1302 rtc(11,  12,   13);

// Init a Time-data structure
Time t;

Color col1 = Color(0  , 0  , 1); // black
Color col2 = Color(0  , 0  , 104); // darkblue 
Color col3 = Color(117, 21  , 0); // orange
Color col4 = Color(255, 50, 0); // yellow
Color col5 = Color(255, 251, 250); //white
// 210-19-0
// 210-21-0

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  analogWrite(REDPIN,   0);
  analogWrite(BLUEPIN,  0);
  analogWrite(GREENPIN, 0);
  rtc.halt(false);
  rtc.writeProtect(true);
  // Serial.begin(9600);
}

Color valInterm(Color col1, Color col2, float pos)
{
   	// res_h = (hsl2[0]-hsl1[0])*pos + hsl1[0]
    // hue value transition can be tricky to compute
    // we have to decide if we go clock wise or counter clowk wise.
    // inspired from here : http://stackoverflow.com/questions/2593832

	Serial.print("pos : ");
	Serial.println(pos);
    // Serial.println("col1 : ");
    // Serial.println(col1.red);
    // Serial.println(col1.green);
    // Serial.println(col1.blue);

    // Serial.println("col2 : ");
    // Serial.println(col2.red);
    // Serial.println(col2.green);
    // Serial.println(col2.blue);

    double hsl1 [3];
    double hsl2 [3];
    double distCCW, distCW;
    col1.rgbToHsl(hsl1);
    col2.rgbToHsl(hsl2);

    if (hsl1[0] >= hsl2[0])
        distCCW = hsl1[0] - hsl2[0];
    else 
       distCCW = 1 + hsl1[0] - hsl2[0];

    if (hsl1[0] >= hsl2[0])
		distCW = 1 + hsl2[0] - hsl1[0]; 
    else
    	distCW = hsl2[0] - hsl1[0];

    //ensure we get the right number of steps by adding remainder to final part
    double res_h, res_l, res_s;
    if (distCW <= distCCW)
        res_h = hsl1[0] + (distCW * pos);
    else
        res_h = hsl1[0] - (distCCW * pos); 
    
    if (res_h < 0) 
    	res_h = 1 + res_h ;
    if (res_h > 1) 
    	res_h = res_h - 1;

    if (hsl2[2] >= hsl1[2])
      res_l = (hsl2[2]-hsl1[2])*pos + hsl1[2];
    else
      res_l = hsl1[2] - (hsl1[2]-hsl2[2])*pos;

    if (hsl2[1] >= hsl1[1])
      res_s = (hsl2[1]-hsl1[1])*pos + hsl1[1];
    else
      res_s = hsl1[1] - (hsl1[1]-hsl2[1])*pos;
	// Serial.println("Res hsl : ");
    // Serial.println(res_h);
	// Serial.println(res_s);
	// Serial.println(res_l);

    Color col = Color::hslToRgb(res_h, res_s, res_l);

    // Serial.println("res col interm : ");
    // Serial.println(col.red);
    // Serial.println(col.green);
    // Serial.println(col.blue);
    Serial.println();
    return col;
}

Color correction(Color col)
{
  // Serial.println("col avant correction");
     // Serial.println(col.red);
     // Serial.println(col.green);
     // Serial.println(col.blue);

	double cor[3] = {255.0/255.0, 212.0/255.0, 164.0/255.0};
	byte r = (int)round((col.red*1.0)*cor[0]);
	byte g = (int)round((col.green*1.0)*cor[1]);
	byte b = (int)round((col.blue*1.0)*cor[2]);

	return Color(r, g, b);
}

void setLedColor(Color col)
{
    // Serial.print("pin red : "); // Serial.println(col.red);
    // Serial.print("pin blue : "); // Serial.println(col.blue);
    // Serial.print("pin green : "); // Serial.println(col.green);
    analogWrite(REDPIN,   col.red);
    analogWrite(BLUEPIN,  col.blue);
    analogWrite(GREENPIN, col.green);	
}

void loop() 
{
  t = rtc.getTime();
  Serial.println(t.min);
  Serial.println(t.hour);
  if (!((t.min == 40) && (t.hour == 7)))
  {
    delay(500);
    return;
  }

  // Serial.println("1 -> 2");
	for(int t=1 ; t < (DUR_TRANS1 + 1) ; ++t)
	{
    	Color res = valInterm(col1, col2, t*1.0/DUR_TRANS1);
      // Serial.print(res.red);
      // Serial.print("-");
      // Serial.print(res.green);
      // Serial.print("-");
      // Serial.print(res.blue);
      // Serial.println();
     	res = correction(res);
     	setLedColor(res);
      delay(SLEEP_TIME);
	}

  // Serial.println("2 -> 3");
  for(int t=1 ; t < (DUR_TRANS2 + 1) ; ++t)
  {
      Color res = valInterm(col2, col3, t*1.0/DUR_TRANS2);
      // double hsl1 [3];
      // res.rgbToHsl(hsl1);
      // Serial.print(hsl1[0]);
      // Serial.print("-");
      // Serial.print(hsl1[1]);
      // Serial.print("-");
      // Serial.print(hsl1[2]);
      // Serial.println();
      res = correction(res);
      setLedColor(res);
      delay(SLEEP_TIME);
  }

  for(int t=1; t < 120; ++t)
      delay(SLEEP_TIME);
  // Serial.println("3 -> 4");
  for(int t=1 ; t < (DUR_TRANS3 + 1) ; ++t)
  {
      Color res = valInterm(col3, col4, t*1.0/DUR_TRANS3);
      // double hsl1 [3];
      // res.rgbToHsl(hsl1);
      // Serial.print(hsl1[0]);
      // Serial.print("-");
      // Serial.print(hsl1[1]);
      // Serial.print("-");
      // Serial.print(hsl1[2]);
      // Serial.println();
      res = correction(res);
      setLedColor(res);
      delay(SLEEP_TIME);
  }
  
  // Serial.println("4 -> 5");
  for(int t=1 ; t < (DUR_TRANS4 + 1) ; ++t)
  {
      Color res = valInterm(col4, col5, t*1.0/DUR_TRANS4);
      // Serial.print(res.red);
      // Serial.print("-");
      // Serial.print(res.green);
      // Serial.print("-");
      // Serial.print(res.blue);
      // Serial.println();
      res = correction(res);
      setLedColor(res);
      delay(SLEEP_TIME);
  }

  while (1)
    setLedColor(correction(col5));
}
