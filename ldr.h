/*
  Light sensor
*/
class LightSensor {
  private:
  int inPin = 2;

  public:
  void ldrSetup(){
    pinMode(inPin, INPUT);
  }

  bool ldrRead(){
    return digitalRead(inPin) == 1;
  }
};

LightSensor ldr;
