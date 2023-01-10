#include "thingProperties.h"
#include <Wire.h>
#include "rgb_lcd.h"


rgb_lcd lcd;

#define relay_water_pump_pin D0 
#define relay_fan_pin D3 
#define relay_light_pin D4 
//#define schedule_light 
//#define time_variable


int soil_sensor = A0;


void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
   
  // put your setup code here, to run once:
  pinMode(relay_water_pump_pin, OUTPUT);
  pinMode(relay_fan_pin, OUTPUT);
  pinMode(relay_light_pin, OUTPUT);
  
    // set up the LCD's number of columns and rows:

  lcd.begin(16, 2);
  delay(100);
  
  
  
  time_read = ArduinoCloud.getLocalTime();

  
}

void loop() {
  ArduinoCloud.update();

  
 sm_sensor=analogRead(soil_sensor);
 delay(500);
 
 if(sm_sensor>1200)
 {
   digitalWrite(relay_water_pump, HIGH);
 }
 else
 {
   digitalWrite(relay_water_pump, LOW);
 }
 
 

  const int analogInPin = A0; // Analog input pin that the Sensor is attached to
  int sensorValue = -1024; // value read from the Soil Moisture

  lcd.clear();
  lcd.print("Soil Moisture:");// print the results to the LCD Display:
  sensorValue = analogRead(analogInPin);// read the analog in value:
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);
  // wait 300 milliseconds before the next loop for the
  //analog-to-digital converter to settle after the last reading:
  delay(300);
  
  
   if (schedule_light.isActive()) 
   {
   // can be configured to be ON between 8am - 5pm 
   digitalWrite(relay_light, HIGH);
   } 
else {
   //can be set to OFF between 5pm - 8am the next morning
   digitalWrite(relay_light, LOW);  
}
  if(ArduinoCloud.connected()){
     time_read = ArduinoCloud.getLocalTime();
  }

 

}


  





/*
  Since Relay1 is READ_WRITE variable, onRelay1Change() is
  executed every time a new value is received from IoT Cloud.
*/
void onRelayWaterPumpChange()  {
   if (relay_water_pump == 1){
    digitalWrite(relay_water_pump_pin , HIGH);
  }
  else{ 
  digitalWrite(relay_water_pump_pin , LOW);
  }
  
  }













/*
  Since RelayFan is READ_WRITE variable, onRelayFanChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onRelayFanChange()  {
  // Add your code here to act upon RelayFan change
  if (relay_fan == 1){
    digitalWrite(relay_fan_pin , HIGH);
  }
  else{ 
  digitalWrite(relay_fan_pin , LOW);
  }
}

/*
  Since RelayLight is READ_WRITE variable, onRelayLightChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onRelayLightChange()  {
  // Add your code here to act upon RelayLight change
  if (relay_light == 1){
    digitalWrite(relay_light_pin , HIGH);
  }
  else{ 
  digitalWrite(relay_light_pin , LOW);
  }
}



/*
  Since ScheduleLight is READ_WRITE variable, onScheduleLightChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onScheduleLightChange()  {
  // Add your code here to act upon ScheduleLight change
}