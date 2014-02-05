
#include <Wire.h>
#include <M24LC128.h>

M24LC128 eeprom;        // Initialize I2C EEPROM object from class constructor
char writeChar = 'X';
char readChar;
uint8_t status;

void setup()
{
  Serial.begin(9600);
  
  Serial.println("Starting in 2 seconds...");
  delay(2000);
  
  eeprom.begin();
  eeprom.write(0, (uint8_t*)&writeChar);
  
  do {
    status = eeprom.pollWIP();
    delay(10);
  } while (status != 0);
  
  eeprom.read(0, (uint8_t*)&readChar);
  Serial.println(readChar);
  Serial.println("Done");  
}


void loop()
{
  // Do nothing
}