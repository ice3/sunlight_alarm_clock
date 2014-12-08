#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
 
#define SLEEP_TIME 200.0     // make this higher to slow down

#define DUR_TRANS1 100.0
#define DUR_TRANS2 100.0
#define DUR_TRANS3 100.0
#define DUR_TRANS4 100.0

#include "Color.h"

Color col1 = Color(0  , 0  , 1); // black
Color col2 = Color(0  , 0  , 204); // darkblue 
Color col3 = Color(204, 0  , 0); // red
Color col4 = Color(255, 238, 0); // yellow
Color col5 = Color(255, 255, 255); //white


void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  analogWrite(REDPIN,   0);
  analogWrite(BLUEPIN,  0);
  analogWrite(GREENPIN, 0);

  Serial.begin(9600);
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

    res_l = abs(hsl2[2]-hsl1[2])*pos + hsl1[2];
    res_s = abs(hsl2[1]-hsl1[1])*pos + hsl1[1];

	// Serial.println("Res hsl : ");
 //    Serial.println(res_h);
	// Serial.println(res_s);
	// Serial.println(res_l);

    Color col = Color::hslToRgb(res_h, res_s, res_l);

    // Serial.println("res col interm : ");
    // Serial.println(col.red);
    // Serial.println(col.green);
    // Serial.println(col.blue);

    return col;
}

Color correction(Color col)
{
	// Serial.println("col avant correction");
 //    Serial.println(col.red);
 //    Serial.println(col.green);
 //    Serial.println(col.blue);

	double cor[3] = {255.0/255.0, 212.0/255.0, 212.0/255.0};
	byte r = (int)round((col.red*1.0)*cor[0]);
	byte g = (int)round((col.green*1.0)*cor[1]);
	byte b = (int)round((col.blue*1.0)*cor[2]);

	return Color(r, g, b);
}

void setLedColor(Color col)
{
    analogWrite(REDPIN,   col.red);
    analogWrite(BLUEPIN,  col.blue);
    analogWrite(GREENPIN, col.green);	
}

void loop() 
{
	for(int t=1 ; t < (DUR_TRANS1 + 1) ; ++t)
	{
    	Color res = valInterm(col1, col2, t*1.0/DUR_TRANS1);
     	res = correction(res);
     	setLedColor(res);
      	delay(SLEEP_TIME * 2);
	}
}
