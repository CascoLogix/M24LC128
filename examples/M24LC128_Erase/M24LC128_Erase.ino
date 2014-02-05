
#include <Wire.h>
#include <M24LC128.h>

M24LC128 eeprom;        // Initialize I2C EEPROM object from class constructor

void setup()
{
  Serial.begin(9600);
  
  Serial.println("Starting in 2 sec...");
  delay(2000);
  
  eeprom.begin();
  
  uint16_t address;
  uint8_t writeStatus;
  for (address = 0; address < M24LC128_MAX_SIZE; address++)
  {
	eeprom.write(address, 0xFF);
	
	do {
	  Serial.println(address);
	  writeStatus = eeprom.pollWIP();
	  delay(5);
	} while (writeStatus != 0);
  }
  
  Serial.println("Done");  
}


void loop()
{
  // Do nothing
}