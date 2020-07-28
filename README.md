
# This is Garduino

Hello there  this is **garduino**,  a set of tools for Arduino Nano applied to watch and water a set of plants.


# Sensor set

- 4x FC28 soil humidity sensor
- 20x4 LCD screen with I2C backpack
- DS18B20 Waterproof temperature sensor* (option A)
- LM393 LDR light sensor
- JSN-SR04T waterproof ultrasonic distance sensor
- ~~28Byj-48 stepper motor~~ (option B)
- ~~10A 2-channel Relay~~* (option B)
- DHT22 temperature and humidity sensor
- HC-06 BT communications module

*Update:*
*since the water temperature sensor is digital we'll use pin 8 from Relay port.
Also BT module connected to IO pins of the Nano board will make impossible working with USB and burning the program, that's why we'll use the Stepper Motor's pins 3 & 4. Remember BT's TX goes to Nano's RX and the other way around*.

## Arduino Nano Pinout

|    Pin            |Sensor |
|----------------|-------------------------------|
|A0|`fc28 #1`|
|A1|`fc28 #2`|
|A2|`fc28 #3`|
|A3|`fc28 #4`|
|A4|`i2C`|
|A5|`i2C`|
|A7|`DS18B20`|
|D11|`DHT22`|
|D10|`JSN-SR04T echo`|
|D9|`JSN-SR04T trigger`|
|D8|`Relay`|
|D6|`28Byj-48`|
|D5|`28Byj-48`|
|D4|`28Byj-48`|
|D3|`28Byj-48`|
|D2|`LDR`|
|TX1|`HC-06`|
|RX1|`HC-06`|

