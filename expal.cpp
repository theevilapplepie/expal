/*

  expal.cpp - Arduino Class that provides easy interfacing to a shift register along with multiplexing via registers/latches

  Copyright (C) 2015 James Vess
  All Rights Reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 =-= Notes =-=

 If you're going to increase the maximum registers from 25 ( Wow ) then you'll need to make
 sure you increase the array sizes of REGDATA and REGPINS.

*/

#include "Arduino.h"
#include "Expal.h"

// Private Functions

void Expal::blinkBit(int pin) {
	  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}

void Expal::blinkBitI(int pin) {
  digitalWrite(pin, LOW);
  digitalWrite(pin, HIGH);
}

void Expal::shiftOutByte(byte data) {

  // Reset the Shift Register
  blinkBitI(SHIFTREG_R);

  // Write out the bits
  int pin = 0;
  byte mask = B00000000;
  for (mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(SHIFTREG_D,HIGH); // send 1
    }
    else{ //if bitwise and resolves to false
      digitalWrite(SHIFTREG_D,LOW); // send 0
    }
    // Write the bit
    blinkBit(SHIFTREG_C);
    pin++;
  }

}

int Expal::isNumeric(int num) {
  if( num >= 0 && num <= 99999 ) {
    return 1;
  }
  return 0;
}

int Expal::isReg(int num) {
  if ( num >= 0 && num <= REGINT ) {
    return 1;
  }
  return 0;
}

// Public Functions

Expal::Expal(int shift_data, int shift_clear, int shift_clock, int registers[] ) {

  // Setup Vars
  SHIFTREG_D = shift_data;
  SHIFTREG_R = shift_clear;
  SHIFTREG_C = shift_clock;

  // Set Shiftreg Pins
  pinMode(SHIFTREG_D, OUTPUT);
  pinMode(SHIFTREG_R, OUTPUT);
  pinMode(SHIFTREG_C, OUTPUT);

  // Set the clear pin to high
  digitalWrite(SHIFTREG_R, HIGH);

  // Iterate the max register to pull all supplied registers
  for(int i = 0; i < sizeof(registers); ++i) {

    if ( !isNumeric(registers[i]) ) {
      continue;
    }
    REGDATA[REGINT] = B00000000;
    REGPINS[REGINT] = registers[i];
    pinMode(registers[i], OUTPUT);
    ++REGINT;
  }

}

void Expal::clear(int registerid) {
  if ( !isReg(registerid) ) {
    return;
  }
  // Reset the Shift Register
  blinkBit(REGPINS[registerid]);
}

void Expal::writeByte(int registerid, byte data) {
  if ( !isReg(registerid) ) {
    return;
  }
  shiftOutByte(data);
  blinkBit(REGPINS[registerid]);
}

void Expal::clearAll() {
  for(int i = 0; i < REGINT; ++i) {
    clear(i);
  }
}