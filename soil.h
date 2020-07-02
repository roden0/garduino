/*
  Soil humidity
*/

class soilSensor{
  public:
  float medianRead;
  void loopSensors(){
    lcd.clear();
    
    int arraySum = 0;
    for (int thisPin = 0; thisPin < sensorCount; thisPin++) {
      pinMode(thisPin, INPUT);
      int r = convertRawValue(analogRead(thisPin)); // get percetage
      displayValues(thisPin,r);                     // show number
      arraySum += r;                                //sum values
    }
    medianRead = arraySum / sensorCount;            // store average
    displayAverage(medianRead);
    
    lcd.backlight();
    delay(5000);
    lcd.noBacklight();
    lcd.clear();
  }

  int getAverage(){
    return (int)medianRead;
  }
  
  private:
  int sensorCount = 4;
  String sPreStr = "S#";
  String sInStr = ": ";
  String sPostStr = "%";
  String aPreStr = "AvH: ";
  String aPostStr = "%";
  
  void displayValues(int i, float r){
    String buf;
    buf += sPreStr;
    buf += String(i);
    buf += sInStr;
    buf += String(r,0);
    buf += sPostStr;
    lcd.setCursor(0,i);
    lcd.print(buf);
  }

  void displayAverage(float r){
    String buf;
    buf += aPreStr;
    buf += String(r,0);
    buf += aPostStr;
    lcd.setCursor(10,0);
    lcd.print(buf);
  }

  int convertRawValue(int read) {
    return map(read,0,1023,100,0);
  }

};

soilSensor sl;
