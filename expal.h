/*

  expal.h - Arduino Class that provides easy interfacing to a shift register along with multiplexing via registers/latches

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

*/

#ifndef EXPAL_LOADED
#define EXPAL_L

#include "Arduino.h"

class Expal {
  public:
    Expal(int shift_data, int shift_clear, int shift_clock, int registers[]);
    void clear(int registerid);
    void clearAll();
    void writeByte(int registerid, byte data);
  private:
    byte REGDATA [25];
    int REGPINS [25];
    int REGINT = 0;
    int SHIFTREG_D;
    int SHIFTREG_R;
    int SHIFTREG_C;
    void shiftOutByte(byte data);
    void blinkBit(int pin);
    void blinkBitI(int pin);
    int isNumeric(int num);
    int isReg(int num);

};

#endif