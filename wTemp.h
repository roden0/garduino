/*
  Water temperature
*/

#include <DallasTemperature.h>
#include <OneWire.h>

#define DS18B20 8

OneWire oneWireObjeto(DS18B20);
DallasTemperature sensorDS18B20(&oneWireObjeto);

class wTempSensor {
  public:
  float wT;
  String tPreStr = "Water Temp: ";
  String tPostStr = "\xDF";

  void wCSetup(){
    pinMode(DS18B20, INPUT);
    sensorDS18B20.begin();
  }

  void wCLoop(){
    sensorDS18B20.requestTemperatures();
    wT = sensorDS18B20.getTempCByIndex(0);
  }

  String readTemp(){
    String buf;
    buf += tPreStr;
    buf += String(wT,0);
    buf += tPostStr;
    return buf;
  }

  void displayValues(){
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print(readTemp());
    delay(5000);
    lcd.noBacklight();
  }
  
};

wTempSensor wC;
