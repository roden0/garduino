/*
  PUMP
*/

#define PUMP 8

class Pump {
  public:

  void pSetup(){
    pinMode(PUMP, OUTPUT);   // set pump pin
    digitalWrite(PUMP, LOW); // cut pump
  }

  void startPump(){
    digitalWrite(PUMP, HIGH);
  }

  void stopPump(){
    digitalWrite(PUMP, LOW);
  }

};

Pump pm;
