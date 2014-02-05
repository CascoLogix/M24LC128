
#include <Wire.h>
#include <M24LC128.h>

M24LC128 eeprom;        // Initialize I2C EEPROM object from class constructor
char text[] = "THIS IS A TEST WRITE";
char readBuf[64];

void setup()
{
  Serial.begin(9600);
  
  Serial.println("Starting in 2 seconds...");
  delay(2000);
  
  eeprom.begin();
  eeprom.write(0, (uint8_t*)text, 21);
  
  delay(20);
  
  Serial.println("Done");  
}


void loop()
{
  
  
}