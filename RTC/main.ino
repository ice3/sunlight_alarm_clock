#include <DS1302.h>

// Init the DS1302
//         RST, DATA, CLK
DS1302 rtc(11,  12,   13);

// Init a Time-data structure
Time t;

void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  
  // Setup Serial connection
  Serial.begin(9600);

  // // The following lines can be commented out to use the values already stored in the DS1302
  // rtc.setDOW(TUESDAY);        // Set Day-of-Week to FRIDAY
  // rtc.setTime(23, 17, 30);     // Set the time to 12:00:00 (24hr format)
  // rtc.setDate(14, 10, 2014);   // Set the date to August 6th, 2010
}

void loop()
{
  // Get data from the DS1302
  t = rtc.getTime();
  
  // Send date over serial connection
  Serial.print("Today is the ");
  Serial.print(t.date, DEC);
  Serial.print(". day of ");
  Serial.print(rtc.getMonthStr());
  Serial.print(" in the year ");
  Serial.print(t.year, DEC);
  Serial.println(".");
  
  // Send Day-of-Week and time
  Serial.print("It is the ");
  Serial.print(t.dow, DEC);
  Serial.print(". day of the week (counting monday as the 1th), and it has passed ");
  Serial.print(t.hour, DEC);
  Serial.print(" hour(s), ");
  Serial.print(t.min, DEC);
  Serial.print(" minute(s) and ");
  Serial.print(t.sec, DEC);
  Serial.println(" second(s) since midnight.");

  // Send a divider for readability
  Serial.println("  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -");
  
  // Wait one second before repeating :)
  delay (1000);
}