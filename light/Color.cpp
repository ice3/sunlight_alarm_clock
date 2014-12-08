// from : 
//  * https://github.com/ratkins/RGBConverter
//  * https://github.com/lucidtronix/ColorArduino

#include "Color.h"

Color :: Color(){
	red = 0;
	green = 0;
	blue = 0;
}

Color :: Color(byte r, byte g, byte b) : 
red(r), green(g), blue(b) { }

void Color::set_color(byte r, byte g, byte b){
  red = r;
  green = g;
  blue = b;
}

int Color::color_16()
{
  int cur_r = red >> 3 ;
  int cur_g = green >> 2 ;
  int cur_b = blue >> 3 ;
  my_color = cur_r  | (cur_g << 5) | (cur_b << 11); 
  return my_color;
}


void Color::rgbToHsl( double hsl[]) {
  double rd = (double) red/255;
  double gd = (double) green/255;
  double bd = (double) blue/255;
  double max = threeway_max(rd, gd, bd);
  double min = threeway_min(rd, gd, bd);
  double h, s, l = (max + min) / 2;
  if (max == min) 
  {
    h = s = 0; // achromatic
  } 
  else 
  {
    double d = max - min;
    s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
    if (max == rd) 
    {
      h = (gd - bd) / d + (gd < bd ? 6 : 0);
    } 
    else if (max == gd) 
    {
      h = (bd - rd) / d + 2;
    } 
    else if (max == bd) 
    {
      h = (rd - gd) / d + 4;
    }
    
    h /= 6;
  }
  hsl[0] = h;
  hsl[1] = s;
  hsl[2] = l;
}


/**
* Converts an HSL color value to RGB. Conversion formula
* adapted from http://en.wikipedia.org/wiki/HSL_color_space.
* Assumes h, s, and l are contained in the set [0, 1] and
* returns r, g, and b in the set [0, 255].
*
* @param Number h The hue
* @param Number s The saturation
* @param Number l The lightness
* @return A color object
*/
Color Color::hslToRgb(double h, double s, double l) 
{
  double r, g, b;
  Serial.println("hslToRgb");
  Serial.println(h);
  Serial.println(s);
  Serial.println(l);
  
  if (s == 0) 
  {
    r = g = b = l; // achromatic
  } 
  else 
  {
    double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    double p = 2 * l - q;
    r = Color::hue2rgb(p, q, h + 1/3);
    g = Color::hue2rgb(p, q, h);
    b = Color::hue2rgb(p, q, h - 1/3);
  }

  byte res_r = (byte)floor(r * 255);
  byte res_g = (byte)floor(g * 255);
  byte res_b = (byte)floor(b * 255);

  Serial.println("hslToRgb");
  Serial.println(r);
  Serial.println(g);
  Serial.println(b);
  return Color(res_r, res_g, res_b);
}

double Color::hue2rgb(double p, double q, double t) 
{
  if(t < 0) t += 1;
  if(t > 1) t -= 1;
  if(t < 1/6) return p + (q - p) * 6 * t;
  if(t < 1/2) return q;
  if(t < 2/3) return p + (q - p) * (2/3 - t) * 6;
  Serial.print("  p : ");
  Serial.println(p);
  return p;
}

double Color::threeway_max(double a, double b, double c) 
{
  return max(a, max(b, c));
}

double Color::threeway_min(double a, double b, double c) 
{
  return min(a, min(b, c));
}