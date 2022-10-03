/*
* I Yash Chaudhary, 000820480 certify that this material is my original work. 
* No other person's work has been used without due acknowledgement.
* I have not made my work available to anyone else."
*/
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire);

// To identify whether temperature device was connected or not at startup
bool tempDeviceConntected = false;
 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  //To store device address
  DeviceAddress device_address;

  Serial.println("\n\nTemprature Application");

  // Finding whether the temperature sensor is connected or not 
  if(DS18B20.getDeviceCount()){
    DS18B20.getAddress(device_address,0);    // Storing the address
    
    Serial.print("Found DS18B20 sensor with address: "); 
    for(uint8_t i = 0; i < 8; i++) {      
      if (device_address[i] < 16) Serial.print("0");
        Serial.print(device_address[i], HEX);
    }
    Serial.println("");
    tempDeviceConntected = true;
  } else {
        Serial.println("No DS18B20 temprature sensors are installed!");
  }
} 

void loop() { 
  // only if the temp sensor is connected
  if(tempDeviceConntected){
    float fTemp; 
  
    // ask DS18B20 for the current temperature 
    DS18B20.requestTemperatures(); 
  
    // fetch the temperature.  We only have 1 sensor, so the index is 0. 
    fTemp = DS18B20.getTempCByIndex(0); 

    String feeling;
    if(fTemp < 10){
      feeling = "Cold!";
    } else if(fTemp < 15){
      feeling = "Cool";
    } else if(fTemp < 25){
      feeling = "Perfect";
    } else if(fTemp < 30){
      feeling = "Warm";
    } else if(fTemp < 35){
      feeling = "Hot";
    } else {
      feeling = "Too Hot!";
    } 
  
    // print the temp to the USB serial monitor 
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or " + feeling); 
  
    // wait 5s (5000ms) before doing this again 
    delay(5000); 
  }
} 
