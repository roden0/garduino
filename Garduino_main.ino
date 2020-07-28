/*
  Garduino Main - Garduino execution container
  Created by R. Encinas, June, 2020.
  Released into the public domain.
*/

/**
  PINOUT
                      +-----+
         +------------| USB |------------+
         |            +-----+            |
         | [ ]D13/SCK        MISO/D12[ ] |
         | [ ]3.3V           MOSI/D11[ ]~|   DHT22
         | [ ]V.ref     ___    SS/D10[ ]~|   wECHO
 FC28_1  | [ ]A0       / N \       D9[ ]~|   wTRIGGER
 FC28_2  | [ ]A1      /  A  \      D8[ ] |   wTemp
 FC28_3  | [ ]A2      \  N  /      D7[ ] |
 FC28_4  | [ ]A3       \_0_/       D6[ ]~|   SM
   I2C   | [ ]A4/SDA               D5[ ]~|   SM
   I2C   | [ ]A5/SCL               D4[ ] |   SM
  wLevel | [ ]A6              INT1/D3[ ]~|   SM
         | [ ]A7              INT0/D2[ ] |   LDR
         | [ ]5V                  GND[ ] |
         | [ ]RST                 RST[ ] |
         | [ ]GND   5V MOSI GND   TX1[ ] |   BT
         | [ ]Vin   [ ] [ ] [ ]   RX1[ ] |   BT
         |          [ ] [ ] [ ]          |
         |          MISO SCK RST         |
         | NANO-V3                       |
         +-------------------------------+

         http://busyducks.com/ascii-art-arduinos
*/

#define DISPLAY_INTERVAL 15000
#define TWO_HOUR_INTERVAL 7200000
#define ONE_MINUTE_INTERVAL 60000
#define HALF_MINUTE_INTERVAL 30000
#define DISPLAY_TIME 3000

#include <SimpleTimer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SimpleTimer timerLight;
SimpleTimer timerSensors;
SimpleTimer timerWater;
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include "htemp.h"
#include "ldr.h"
#include "soil.h"
#include "wlevel.h"
//#include "pump.h"
#include "wTemp.h"

bool isNight = false;


void showMode(bool mode){
  showInfo(mode ? "Night mode": "Daytime mode");  
}

void storeLight(){
  isNight = ldr.ldrRead();
  showMode(isNight);
}

void showInfo(String message) {
  lcd.clear();
  lcd.backlight();
  lcd.print(message);
  delay(DISPLAY_TIME);
  lcd.clear();
  lcd.noBacklight();
}

void showStartUpMessage(){
  lcd.clear();
  lcd.backlight();
  lcd.print("Booting");
  delay(1000);
  lcd.setCursor(7,0);
  lcd.print(".");
  delay(1500);
  lcd.setCursor(8,0);
  lcd.print(".");
  delay(1500);
  lcd.setCursor(9,0);
  lcd.print(".");
  delay(1500);
  showInfo("Welcome to Garduino");
}

void setup() {
  // init screen
  lcd.init();
  lcd.clear();
  showStartUpMessage();

  // set pump
  //pm.pSetup();

  //init DHT22
  ht.htSetup();

  // init LDR
  ldr.ldrSetup();

  // init water temperature
  wC.wCSetup();

  // level setup
  lvl.wSetup();

  timerLight.setInterval(TWO_HOUR_INTERVAL);
  timerSensors.setInterval(HALF_MINUTE_INTERVAL);
}

void loop() {

  if(timerLight.isReady()){
    storeLight();
  }

  if (timerSensors.isReady()) {
    showMode(isNight);
    
    //Get DHT22 values
    ht.htLoop();
    ht.displayValues();

    // Get soil humidity
    sl.loopSensors();

    // Get water level
    lvl.getWaterLevel();

    // Get water temperature
    wC.wCLoop();
    wC.displayValues();
    
    if(isNight && sl.getAverage() < 49 && lvl.hasWater()){
      //showInfo("Watering started");
      //pm.startPump();
      //delay(HALF_MINUTE_INTERVAL);
      //pm.stopPump();
      //showInfo("Watering finished");
      
    }
    
    timerSensors.reset();
  }
  
}
