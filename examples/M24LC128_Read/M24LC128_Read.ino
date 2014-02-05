
#include <Wire.h>
#include <M24LC128.h>

M24LC128 eeprom;        // Initialize I2C EEPROM object from class constructor
char readBuf[32];

void setup()
{
  Serial.begin(9600);
  
  Serial.println("Starting in 2 seconds...");
  delay(2000);

  eeprom.begin();
  eeprom.read(0, (uint8_t*)readBuf, 21);
  Serial.println(readBuf); 
  Serial.println("Done");
}


void loop()
{
  // Do nothing 
}