/*
  Humidity and Temperature DHT22 sensor
*/
#include <DHT.h>
#include <DHT_U.h>  

#define DHTTYPE DHT22
#define DHT22_PIN 11

DHT dht(DHT22_PIN, DHTTYPE);

class HTSensor {
  private:
  float h;
  float t;
  float hic;

  public:
  String humPreStr = "H: ";
  String humPostStr = "%";
  String tempPreStr = "T: ";
  String tempPostStr = "\xDF";
  String feelPreStr = "Feels: ";
  
  void htSetup(){
    dht.begin();
  }

  void htLoop(){
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    t = dht.readTemperature();
  
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      return;
    }
    // Compute heat index in Celsius
    hic = dht.computeHeatIndex(t, h, false);
  }

  String hRead(){
    String buf;
    buf += humPreStr;
    buf += String(h,0);
    buf += humPostStr;
    return buf;
  }

  String tRead(){
    String buf;
    buf += tempPreStr;
    buf += String(t,0);
    buf += tempPostStr;
    return buf;
  }

  String fRead(){
    String buf;
    buf += feelPreStr;
    buf += String(hic,0);
    buf += tempPostStr;
    return buf;
  }

  void displayValues(){
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print(hRead());
    lcd.setCursor(0,1);
    lcd.print(tRead());
    lcd.setCursor(0,3);
    lcd.print(fRead());
    delay(5000);
    lcd.noBacklight();
  }
  
};

HTSensor ht;
