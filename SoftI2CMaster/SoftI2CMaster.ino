/* 
  Software I2C master protocol implementation to any microcontroller: Atmega, STM32, ESP32 ect. 
  Thanks ChatGPT for help.

  
  By Serhii Trush for MIT License
  https://github.com/techn0man1ac/SoftwareI2CIMaster
*/


#define SDA_PIN 4
#define SCL_PIN 5

#define LED_BUILTIN 13

#define deviceAddress 0x08  // 7 bit slave address
bool State = LOW;

void i2c_start() {
  pinMode(SDA_PIN, OUTPUT);
  pinMode(SCL_PIN, OUTPUT);
  digitalWrite(SDA_PIN, HIGH);
  digitalWrite(SCL_PIN, HIGH);
  delayMicroseconds(100);
  digitalWrite(SDA_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(SCL_PIN, LOW);
}

void i2c_stop() {
  pinMode(SDA_PIN, OUTPUT);
  digitalWrite(SDA_PIN, LOW);
  digitalWrite(SCL_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(SDA_PIN, HIGH);
}

uint8_t i2c_send_byte(uint8_t byte) {
  pinMode(SDA_PIN, OUTPUT);
  for (int i = 7; i >= 0; i--) {
    digitalWrite(SDA_PIN, (byte >> i) & 0x01);  // bitwise AND operation(00,01,10->0 and 11->1)
    digitalWrite(SCL_PIN, HIGH);
    delayMicroseconds(2);
    digitalWrite(SCL_PIN, LOW);
    delayMicroseconds(2);
  }
  pinMode(SDA_PIN, INPUT);
  digitalWrite(SDA_PIN, HIGH);
  digitalWrite(SCL_PIN, HIGH);
  delayMicroseconds(2);
  uint8_t ack = digitalRead(SDA_PIN);  // Gotcha
  digitalWrite(SCL_PIN, LOW);
  delayMicroseconds(2);
  return ack;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SDA_PIN, OUTPUT);
  pinMode(SCL_PIN, OUTPUT);
  digitalWrite(SDA_PIN, HIGH);
  digitalWrite(SCL_PIN, HIGH);
  delay(1000);
}

void loop() {
  digitalWrite(LED_BUILTIN, State);
  // Example send data to I2C slave with address 0x08

  uint8_t dataToSend = State;

  i2c_start();
  i2c_send_byte((deviceAddress << 1) | 0);  // send adress with write bit(0-wr)
  i2c_send_byte(dataToSend);
  i2c_stop();

  Serial.println(State);  // print State value
  State = !State;

  delay(1000);  
}
