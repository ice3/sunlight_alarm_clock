/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "Color.h"


// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            4
#define MAX_PIXEL_NUMBER 100

const char* ssid     = "***";
const char* password = "***";

// Create an instance of the server
// specify the port to listen on as an argument
ESP8266WebServer server(80);

int num_pixels = 10;
int steps = 1000;
bool inSimulation = false;
unsigned long lastRunned = 0;
int interval_between_steps = 1000;  // 1s between each steps
int start_transition_1, start_transition_2, start_transition_3, start_transition_4, transition_duration;

String webString;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(MAX_PIXEL_NUMBER, PIN, NEO_GRB + NEO_KHZ800);



Color col1 = Color(1  , 1  , 1); // black
Color col2 = Color(0  , 0  , 104); // darkblue 
Color col3 = Color(117, 21  , 0); // orange
Color col4 = Color(255, 50, 0); // yellow
Color col5 = Color(255, 251, 251); //white

bool nextStep(int steps){
  /*
   * Arguments: steps: the number of steps remaining
   * Returns a boolean telling if the annimation should continue
   * 
   */
  lastRunned = millis();

  // reset the strip
  for(int i=0;i< MAX_PIXEL_NUMBER;i++)
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));

  Color from, to;
  float pos;
  if (steps < start_transition_4){
    from = col4;
    to = col5;
    pos = start_transition_4 - steps;  

  }
  else if (steps < start_transition_3){
    from = col3;
    to = col4;
    pos = start_transition_3 - steps;  
  }
  else if (steps < start_transition_2){
    from = col2;
    to = col3;
    pos = start_transition_2 - steps;  
  }
  else if (steps < start_transition_1){
    from = col1;
    to = col2;
    pos = start_transition_1 - steps;  
  }

  pos /= transition_duration;  // 0<= pos <= 1
  Color sunlight = Color::valInterm(from, to, pos);
  Serial.print("r:" + String(sunlight.red) + " - g:" + String(sunlight.green) + " - b:" + String(sunlight.blue));
  
  for(int i=0;i< (num_pixels);i++){
    pixels.setPixelColor(i, sunlight.red, sunlight.green, sunlight.blue); 
  }
  pixels.show(); // This sends the updated pixel color to the hardware.

  Serial.println("");

  return (steps > 0);
}

bool runSimulation(){
  /*Serial.println("steps (run simulation) : " + String(steps));
  Serial.println("(millis() - lastRunned) : " + String((millis() - lastRunned)));*/
  if ((millis() - lastRunned) < interval_between_steps)
      return true;

  steps -= 1;
  inSimulation = nextStep(steps);
}

void handle_root() {
  server.send(200, "text/plain", "Hello from the dawn simulation.");
  delay(100);
}

void setup() {
  Serial.begin(115200);
  delay(10);

  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.println(WiFi.localIP());

  server.on("/", handle_root);

  server.on("/runSimulation", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    if(server.hasArg("seconds")) {
      steps = server.arg("seconds").toInt();
      start_transition_1 = steps;
      start_transition_2 = (int)(steps * (3.0 / 4.0));
      start_transition_3 = (int)(steps * (2.0 / 4.0));
      start_transition_4 = (int)(steps * (1.0 / 4.0));
      transition_duration = (int)(steps * (1.0 / 4.0));
    }
    
    if(server.hasArg("nbLeds")) {
      num_pixels = server.arg("nbLeds").toInt();
    }
    
    inSimulation = true;
    webString="Simulation running for: " + String(steps) + " seconds";   // Arduino has a hard time with float to string
    server.send(200, "text/plain", webString);            // send to someones browser when asked
  });

  server.on("/stopSimulation", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    for(int i=0;i< MAX_PIXEL_NUMBER;i++)
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
    
    inSimulation = false;
    webString="Simulation stopped";   // Arduino has a hard time with float to string
    server.send(200, "text/plain", webString);            // send to someones browser when asked
  });

  server.on("/infos", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    webString="Simulation status :";
    webString+="<ul>";
    webString+="<li>Running: " + String(inSimulation) +"</li>";
    webString+="<li>Number of leds:" + String(num_pixels) +"</li>";
    webString+="<li>Steps remaining: " + String(steps) +"</li>";
    webString+="<li>Transitions start:<ul>";
    webString+="<li>1:"+String(start_transition_1)+"</li>";
    webString+="<li>2:"+String(start_transition_2)+"</li>";
    webString+="<li>3:"+String(start_transition_3)+"</li>";
    webString+="<li>4:"+String(start_transition_4)+"</li>";
    webString+="</ul></li>";    
    webString+="</ul>";
    server.send(200, "text/html", webString);            // send to someones browser when asked
  });
 
 server.on("/config", [](){  // if you add this subdirectory to your webserver call, you get text below :)
     if(server.hasArg("nbLeds")) {
      num_pixels = server.arg("nbLeds").toInt();
     } 

    webString="Configuration set:";
    webString+="<ul>";
    webString+="<li>num_pixels = "+String(num_pixels)+"</li>";
    webString+="</ul>";

    server.send(200, "text/plain", webString);            // send to someones browser when asked
  });

 server.on("/testColor", [](){  // if you add this subdirectory to your webserver call, you get text below :)
     int r, g, b;
     
     if(server.hasArg("r")) {
      r = server.arg("r").toInt();
     } 

     if(server.hasArg("g")) {
      g = server.arg("g").toInt();
     } 

     if(server.hasArg("b")) {
      b = server.arg("b").toInt();
     } 

    for(int i=0;i< num_pixels;i++)
      pixels.setPixelColor(i, pixels.Color(r, g, b));

    webString="Color set to : r=" + String(r) + " g=" + String(g) + " b="+ String(b);

    server.send(200, "text/plain", webString);            // send to someones browser when asked
  });

  
  server.begin();
  Serial.println("HTTP server started");

  pixels.begin();
  pixels.show();
  Serial.println("Neopixels started");
  
}

void loop() {
  server.handleClient();
  
  if(inSimulation)
    runSimulation();
}

