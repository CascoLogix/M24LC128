/** 
 *  M24LC128.cpp
 *  
 *  This is a library for interfacing to the Microchip M24LC128 I2C 128Kbit
 *  EEPROM chip.  
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


#include <Arduino.h>
#include <M24LC128.h>
#include <Wire.h>


#define M24LC128_I2C_ADDRESS				(0x50)


// Constructor
M24LC128::M24LC128()
{

}


// Initialize interfaces
void M24LC128::begin()
{  
	Wire.begin();        					// Join I2C bus as a Master
}


// Read a byte from the EEPROM
uint8_t M24LC128::read(uint16_t address)	
{
	uint8_t data;
	
	Wire.beginTransmission(M24LC128_I2C_ADDRESS);		// Send start condition, address and write bit
	Wire.write((address >> 8) & 0xFF);					// Send MSB of address
	Wire.write(address & 0xFF);							// Send LSB of address
	
	Wire.requestFrom(M24LC128_I2C_ADDRESS, 1);			// Send repeated start condition, address and read bit
	data = Wire.read();									// Read the byte
	Wire.endTransmission();								// Send stop condition
	
	return data;
}


// Read several bytes from the EEPROM
void M24LC128::read(uint16_t address, uint8_t * pData, uint16_t numBytes)	
{
	Wire.beginTransmission(M24LC128_I2C_ADDRESS);		// Send start condition, address and write bit
	Wire.write((address >> 8) & 0xFF);					// Send MSB of address
	Wire.write(address & 0xFF);							// Send LSB of address
	
	Wire.requestFrom(M24LC128_I2C_ADDRESS, numBytes);	// Send repeated start condition, address and read bit
	for (numBytes; numBytes > 0; numBytes--)
	{
		*pData = Wire.read();							// Read the byte
		pData++;										// Increment buffer pointer
	}
	Wire.endTransmission();								// Send stop condition
}


// Write a byte to the EEPROM
void M24LC128::write(uint16_t address, uint8_t data)	
{  
	Wire.beginTransmission(M24LC128_I2C_ADDRESS);		// Send start condition, address and write bit
	Wire.write((address >> 8) & 0xFF);					// Send MSB of address
	Wire.write(address & 0xFF);							// Send LSB of address
	
	Wire.write(data);									// Write the byte
	Wire.endTransmission();								// Send stop condition
}


// Write several bytes to the EEPROM (up to 64 bytes (1 page) can be written at a time)
void M24LC128::write(uint16_t address, uint8_t * pData, uint8_t numBytes)
{  
	Wire.beginTransmission(M24LC128_I2C_ADDRESS);		// Send start condition, address and write bit
	Wire.write((address >> 8) & 0xFF);					// Send MSB of address
	Wire.write(address & 0xFF);							// Send LSB of address
	
	for (numBytes; numBytes > 0; numBytes--)
	{
		Wire.write(*pData);								// Write the byte
		pData++;										// Increment buffer pointer
	}
	Wire.endTransmission();								// Send stop condition
}


// Fill specified EEPROM addresses with specified data
void M24LC128::fill(uint16_t address, uint8_t data, uint8_t numBytes)
{
	uint16_t pageBoundary;
	
	pageBoundary = M24LC128_PAGE_SIZE - 1;				// Set first page boundary
	
	for (numBytes; numBytes > 0; numBytes--)
	{
		Wire.beginTransmission(M24LC128_I2C_ADDRESS);	// Send start condition, address and write bit
		Wire.write((address >> 8) & 0xFF);				// Send MSB of address
		Wire.write(address & 0xFF);						// Send LSB of address
	
		Wire.write(data);								// Write byte
		
		if (address == pageBoundary)					// Check for page boundary
		{
			Wire.endTransmission();						// Send stop condition
			
			pageBoundary += M24LC128_PAGE_SIZE;			// Get next page boundary
			address += M24LC128_PAGE_SIZE;				// Set next start address
			
			do {
				delay(3);								// Wait some time
			} while (this->pollWIP());					// Poll WIP status
		}		
	}
	
	Wire.endTransmission();								// Send stop condition
}


// Fill all EEPROM addresses with specified data
void M24LC128::fillAll(uint8_t data)
{  
	this->fill(0, data, M24LC128_MAX_SIZE);
}


uint8_t M24LC128::pollWIP()								// Poll for Write-in-progress (WIP)
{
	uint8_t retVal;
	
	Wire.beginTransmission(M24LC128_I2C_ADDRESS);		// Send start condition, address and write bit
	retVal = Wire.endTransmission();					// Send stop condition and capture ACK/NACK
	
	return retVal;										// Return ACK/NACK
}
