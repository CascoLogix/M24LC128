/** 
 *  M24LC128_Write.ino
 *  
 *  This is a demonstration for writing to the Microchip 24LC128 I2C EEPROM 
 *  chip using the M24LC128 library.  
 *
 *  Copyright (C) 2014  Clint Stevenson (CascoLogix http://cascologix.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 
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