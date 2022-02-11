#include <Adafruit_Sensor.h>            
#include <DHT.h>
#include <Wire.h>                       
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define pinSensor 2
DHT dht(pinSensor,DHT11);

//SAMPLING TIME
int time_sam=9000;

//LAST PIXEL POSITION
int x_p=3;                            
int y_p;                           



void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {            //DISPLAY INITIALIZATION
    while(true); 
  }
  display.clearDisplay();
  
  dht.begin();                                                          //SENSOR INIZIALIZATION
}




void loop() {
  int humidity_percentage = dht.readHumidity();                         //SAMPLING
  
  if (x_p==127){                                                        //OVERFLOW DISPLAY
      display.clearDisplay();
      x_p=3;
    }

  y_p = map(humidity_percentage, 0, 100,63,17);

  
  axis();

  //HUMIDITY TEXT
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(57,0);             
  display.println(("H:"));
  display.fillRect(80,0,24,16,SSD1306_BLACK);
  display.setCursor(80,0);
  display.println((humidity_percentage));
  display.setCursor(110,0);
  display.println(("%"));

  //GRAPH
  display.drawPixel(x_p++, y_p,SSD1306_WHITE);
  
  display.display();
  
  delay(time_sam);
}



void axis(){
   display.drawLine(2,61,127,61, SSD1306_WHITE);      //X AXIS
   display.drawLine(125,63,127,61, SSD1306_WHITE);
   display.drawLine(125,59,127,61, SSD1306_WHITE);
   
   display.drawLine(2,61,2,17, SSD1306_WHITE);        //Y AXIS
   display.drawLine(0,19,2,17, SSD1306_WHITE);
   display.drawLine(4,19,2,17, SSD1306_WHITE);
   display.display();
 }
