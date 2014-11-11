// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
 
#define FADESPEED 20     // make this higher to slow down
 
String inData;

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  analogWrite(REDPIN,   0);
  analogWrite(BLUEPIN,  0);
  analogWrite(GREENPIN, 0);

  Serial.begin(9600);
}
 
 
void loop() {
  int r, g, b;
  String content = "";
  char j_c, r_c, g_c, b_c;

    while (Serial.available() > 0)
    {
        char recieved = Serial.read();
        inData += recieved; 

        // Process message when new line character is recieved
        if (recieved == '\n')
        {
            Serial.print("Arduino Received: ");
            Serial.print(inData);
            int commaIndex = inData.indexOf(',');
            int secondCommaIndex = inData.indexOf(',', commaIndex+1);

            String firstValue = inData.substring(0, commaIndex);
            String secondValue = inData.substring(commaIndex+1, secondCommaIndex);
            String thirdValue = inData.substring(secondCommaIndex+1, inData.length()-1); // To the end of the string
            
            Serial.print("Parsed: ");
            Serial.println(thirdValue);

            r = firstValue.toInt();
            g = secondValue.toInt();
            b = thirdValue.toInt();

            analogWrite(REDPIN,   r);
            analogWrite(BLUEPIN,  b);
            analogWrite(GREENPIN, g);
            inData = ""; // Clear recieved buffer
        }
    }

}

