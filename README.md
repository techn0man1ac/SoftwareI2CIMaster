# SoftwareI2CIMaster

![Job](https://raw.githubusercontent.com/techn0man1ac/SoftwareI2CIMaster/main/Img/ezgif-2-92b3f45327.gif "Job")

Software I2C master protocol implementation to any microcontroller: Atmega, STM32, ESP32, Arduino code here:

https://github.com/techn0man1ac/SoftwareI2CIMaster/tree/main/SoftI2CMaster

Slave side I2C work in normal mode(SDA-> A4 SCL-> A5).

Into slave side i use this simple code:

```cpp
#include <Wire.h>

#define LED_BUILTIN 13
bool State = LOW;

void setup() {
  Wire.begin(8);                 // join I2C bus with address #8
  Wire.onReceive(receiveEvent);  // register event
  Serial.begin(115200);          // start serial for output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, State);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  State = Wire.read();    // receive byte as an integer
  Serial.println(State);  // print the integer
}

```


