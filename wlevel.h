/*
  Water level
*/

#define TRIGPIN 9              // Define Trig  pin
#define ECHOPIN 10             // Define Echo pin

#define MAX_DISTANCE 400

#define PI 3.14159

class WaterLevel {
  public:
  // TANK DIMENSIONS      
  const int diameter = 65;             //internal Diameter
  const int depth = 100;               //total depth of tank, sensor to base
  const int totalLiters = 220;         // max capacity
  const int area = PI * ((diameter / 2) * (diameter / 2));  //area of tank base
  
  void wSetup(){
    pinMode(TRIGPIN, OUTPUT);
    pinMode(ECHOPIN, INPUT);
  }

  float currentLitres;
  float distance;
  String lPreStr = "Remaining: ";
  String lPostStr = " L";
  String dPreStr = "Water Level: ";
  String dPostStr = "cm";

  bool hasWater(){
    return distance > 20;
  }
  
  float getLitres(){
    return currentLitres;
  }

  float calcLitres(float d){
    return (area * d) / 1000;
  }
  
  void getWaterLevel(){
    
    digitalWrite(TRIGPIN, LOW); // Set the trigger pin to low
    delayMicroseconds(2);

    digitalWrite(TRIGPIN, HIGH); // Send a 20uS high to trigger ranging
    delayMicroseconds(20);

    digitalWrite(TRIGPIN, LOW); // Send pin low again

    distance = pulseIn(ECHOPIN, HIGH,26000); // Read in times pulse

    //distance /= 58;
    distance /= 13.35;          //13.3511 because the spread of soundwave in water

    currentLitres = calcLitres(distance);

    displayValues(dRead(distance),lRead(currentLitres));
    
    delay(100);
  }

  String dRead(float r){
    String buf;
    buf += dPreStr;
    buf += String(r,0);
    buf += dPostStr;
    return buf;
  }
  
  String lRead(float l){
    String buf;
    buf += lPreStr;
    buf += String(l,0);
    buf += lPostStr;
    return buf;
  }

  void displayValues(String dMessage, String lMessage){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(dMessage);
    lcd.setCursor(0,1);
    lcd.print(lMessage);
    lcd.backlight();
    delay(3000);
    lcd.noBacklight();
    lcd.clear();
  }

};

WaterLevel lvl;
