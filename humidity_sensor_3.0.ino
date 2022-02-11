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
int time_sam=8000;

//ISTOGRAM ROW
int row;

//SECOND-LAST PIXEL POSITION
int y_p_pre;

//MAXIMUM DATA E MINIMUM DATA
int max_hum=0;
int min_hum=99;

//LAST PIXEL POSITION
int x_p=3;                            
int y_p;                           



void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {    //DISPLAY INITIALIZATION
    while(true); 
  }
  display.clearDisplay();

  dht.begin();                                                  //SENSOR INITIALIZATION
}




void loop() {

  int humidity_percentage = dht.readHumidity();                 //SAMPLING

  if(humidity_percentage>max_hum){                              
    max_hum=humidity_percentage;
  }

  if(humidity_percentage<min_hum){
    min_hum=humidity_percentage;
  }


  
  if (x_p==127){                                                //OVERFLOW DISPLAY
      display.clearDisplay();
      x_p=3;
    }

    
  row = map(humidity_percentage, 0, 100,0,127);
  y_p = map(humidity_percentage, 0, 100,63,17);

  
  axis();

  //ISTOGRAM
  display.drawRect(0,0,127,16,SSD1306_WHITE);
  display.fillRect(0,0,row,16,SSD1306_WHITE);

  //CURRENT HUMIDITY TEXT
  display.setTextSize(2);             
  display.setTextColor(SSD1306_BLACK);        
  display.setCursor(1,1);             
  display.println(("H:"));
  display.fillRect(80,0,24,16,SSD1306_WHITE);
  display.setCursor(21,1);
  display.println((humidity_percentage));
  display.setCursor(45,1);
  display.println(("%"));

  //MAX HUMIDITY TEXT
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(4,53);
  display.println(("MAX:"));
  display.fillRect(28,53,11,8,SSD1306_BLACK);
  display.setCursor(28,53);
  display.println((max_hum));
  display.setCursor(40,53);
  display.println(("%"));
  

  //MIN HUMIDITY TEXT
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(60,53);
  display.println(("min:"));
  display.fillRect(84,53,11,8,SSD1306_BLACK);
  display.setCursor(84,53);
  display.println((min_hum));
  display.setCursor(96,53);
  display.println(("%"));
  
  

  //GRAPH
  display.drawLine(x_p, y_p_pre,x_p, y_p,SSD1306_WHITE);

  x_p++;
  y_p_pre=y_p;
  
  
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
