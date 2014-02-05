/** 
 *  M24LC128.h
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




#ifndef M24LC128_h
#define M24LC128_h


#include <stdint.h>


#define M24LC128_PAGE_SIZE			(64)
#define M24LC128_NUM_PAGES			(256)
#define M24LC128_MAX_SIZE			(M24LC128_PAGE_SIZE * M24LC128_NUM_PAGES)


class M24LC128 {
public:
	M24LC128();															// Constructor
	void begin();														// Initialize interfaces
	uint8_t read(uint16_t address);										// Read a single byte
	void read(uint16_t address, uint8_t * pData, uint16_t numBytes);	// Read bytes to a buffer
	void write(uint16_t address, uint8_t pData);						// Write a single byte
	void write(uint16_t address, uint8_t * pData, uint8_t numBytes);	// Write bytes from a buffer
	void fill(uint16_t address, uint8_t data, uint8_t numBytes);		// Fill specified range with specified data
	void fillAll(uint8_t data);											// Fill all with specified data
	uint8_t pollWIP();													// Poll for Write-in-progress (WIP)
};

//extern M24LC128 M24LC128;

#endif // M24LC128_h