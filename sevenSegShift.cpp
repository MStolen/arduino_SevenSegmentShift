#include "Arduino.h"
#include "sevenSegShift.h"
#include <avr/pgmspace.h>

SevenSegShift::SevenSegShift(int dataPin, int clockPin, int latchPin, Common common) {

    pinMode(dataPin,OUTPUT);
    pinMode(clockPin,OUTPUT);
    pinMode(latchPin,OUTPUT);

    _dataPin=dataPin;
    _clockPin=clockPin;
    _latchPin=latchPin;
    _common=common;
    setVal(0x8); //initializes seven segment to 8
}

void SevenSegShift::setVal(int hexNum) {
    //sends values to shift register
    
    //set values for common annode display
    //0 is MSB and dp(always off) is LSB
    static const byte SEGCONST[17]={0x03,0x9F,0x25,0x0D,0x99,0x49,0x41,0x1F,0x01,0x09,0x11,0xC1,0x63,0x85,0x61,0x71,0xFC};
    // w/o flash mem ^
    //{0,1,...,9,A,...,F,'-'}
    
    //static const PROGMEM byte SEGCONST[17]={0x03,0x9F,0x25,0x0D,0x99,0x49,0x41,0x1F,0x01,0x09,0x11,0xC1,0x63,0x85,0x61,0x71,0xFC};
    // with flash mem ^
    static byte dataOut; //data to send to shift register
    dataOut=SEGCONST[hexNum]; // w/o stored in flash
    //dataOut=pgm_read_byte_near(SEGCONST+hexNum); // w/flash
    if (_common==CATHODE) {
        dataOut=~dataOut;
    }
    
    digitalWrite(_latchPin,0); //making sure latch low
    
    shiftOut(_dataPin,_clockPin,LSBFIRST,dataOut);
    
    digitalWrite(_latchPin,1); //updating shift register
    digitalWrite(_latchPin,0); //latch ready to update
}

int SevenSegShift::serial2seg(int serialVal) {
    //takes ASCII value and converts it to hex value
    if (serialVal>=48&&serialVal<=57) { //0-9
        return serialVal-48;
    } else if (serialVal>=65 && serialVal<=70) { //A-F
        return serialVal-55;
    } else if (serialVal>=97 && serialVal<=102){ //a-f
        return serialVal-87;
    } else {
        return 16; //all others
    }
}
