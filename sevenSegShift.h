/*
    This is a basic library for arduino. It uses a shift
    register to display a value on a common annode
    7-segment LED display
*/
#ifndef SevenSegShift_h
#define SevenSegShift_h

#include "Arduino.h"

enum Common {ANNODE,CATHODE};

class SevenSegShift
{
  public:
    SevenSegShift(int dataPin, int clockPin, int latchPin, Common common);
    void setVal(int hexNum);
    int serial2seg(int serialVal);
  private:
    int _dataPin;
    int _clockPin;
    int _latchPin;
    Common _common;
};

#endif