
#include <Midiboy.h>
#include "Arduboy.h"
Arduboy arduboy;
//counter for sound
float floatI = 0;

float tempo = 0.5;

int currentsound = 4;

/* Sound definitions */
byte sound1(int i) {
  return i / 13 >> (1 + ((i >> 12) & 3)) | i / 2 >> 2 & (i / 6) >> 7 | i & 31 * i * (i >> 8);
}
byte sound2(int i) {
  return (i / 3 >> (i % 40 + 5) | i / (24 + i & 3) >> (i % (15 - ((i >> 15) % 8) * 6) + 5)) / 8;
}
byte sound3(int i) {
  return i >> 2;
}
byte sound4(int i) {
  return int( ((sin(i * 0.005) / 2.0) + 1) * 127);
}
byte sound5(int i) {
  return i * ((i >> 12 | i >> 8) & 63 & i >> 4);
}
byte sound6(int i) {
  return (i ^ i >> 8) | i << 3 & 56 ^ i;
}
byte sound7(int i) {
  return i * 4 / 64 | i & i / 128;
}
byte sound8(int i) {
  return ((i << 1) ^ ((i << 1) + (i >> 7)&i >> 12)) | i >> (4 - (1 ^ 7 & (i >> 19))) | i >> 7;
}
byte sound9(int i) {
  return (i*(i>>8+i>>9)*100)+sin(i);
  //return int(i & (i << 3) % (72022 & (i >> 9)) * 283742783 & i);
  //i*i * ~((i >> 16 | i >> 12) & 215 & ~i >> 8);
  //(t*(t>>8+t>>9)*100)+sin(t)
}
byte sound10(int i) {
  return  i * ((i >> 5 | i >> 8) >> (i >> 16));
}


void setup() {
  /*
     Midiboy.begin();
     Midiboy.setButtonRepeatMs(50);
  */
  arduboy.begin();
  arduboy.setFrameRate(15);
  pinMode(PIN_SPEAKER_1, OUTPUT);
}

void print_cur(String Bytes, String Bytes2) {
  arduboy.setCursor(1 + 2, 8);
  arduboy.print(Bytes);
  arduboy.setCursor(1 + 2, 18);
  arduboy.print(Bytes2);
}

byte getSound(byte soundtype, int i) {
  //yes yes, can be done with function array pointers.
  switch (soundtype) {
    case 1:
      {
        return  sound1(i);
      }
    case 2:
      {
        return  sound2(i);
      }
    case 3:
      {
        return  sound3(i);
      }
    case 4:
      {
        return  sound4(i);
      }
    case 5:
      {
        return  sound5(i);
      }
    case 6:
      {
        return  sound6(i);
      }
    case 7:
      {
        return  sound7(i);
      }
    case 8:
      {
        return  sound8(i);
      }
    case 9:
      {
        return  sound9(i);
      }
    case 10:
      {
        return  sound10(i);
      }
  }
}

void loop() {

  // always write the sound out begore doing or not doing arduboy stuff
  int i = (int)floatI;
  int a = getSound(currentsound, i);

  digitalWrite(PIN_SPEAKER_1, a % 2); //writing the output sound

  floatI += tempo; //float counter so that you can set tempo

  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();

  for (int x = 0; x < 256; x++)
  {
    int y = getSound(currentsound, floatI + x);
    arduboy.drawPixel(x, y % 64, 1);
  }

  if (arduboy.pressed(A_BUTTON) ) {
    tempo += 0.1;
  }

  if (arduboy.pressed(B_BUTTON) ) {
    tempo -= 0.1;
  }

  if (arduboy.pressed(UP_BUTTON) ) {
    floatI = 0;
    if (arduboy.pressed(A_BUTTON) ) {
      currentsound = 5;
      print_cur(F("i * ((i>>12|i>>8))"), F("&63&i>>4)"));
    } else {
      currentsound = 1;
      print_cur(F("i/13>>(1+((i>>12)&3))|i/2>>"), F("2&(i/6)>>7|i&31*i*(i>>8)"));
    }
  }

  if (arduboy.pressed(DOWN_BUTTON) ) {
    floatI = 0;
    if (arduboy.pressed(A_BUTTON) ) {
      currentsound = 6;
      print_cur(F("(i^i>>8)|"), F("i<<3&56^i"));
    } else {
      currentsound = 2;
      print_cur(F("i/3>>(i%40+5)|i/(24+i&3)"), F(" >(i%(15-((i>>15)%8)*6)+5))/8"));
    }
  }

  if (arduboy.pressed(LEFT_BUTTON) ) {
    floatI = 0;
    if (arduboy.pressed(A_BUTTON) ) {
      currentsound = 7;
      print_cur(F("i*4/64|i&i/128)"), F("up!"));
    } else if (arduboy.pressed(B_BUTTON) ) {
      currentsound = 9;
      print_cur(F("(i*(i>>8+i>>9)*100)"), F("sin(i)"));
    } else {
      currentsound = 3;
      print_cur(F("i >> 2"), F("slick"));
    }
  }

  if (arduboy.pressed(RIGHT_BUTTON) ) {
    floatI = 0;
    if (arduboy.pressed(A_BUTTON) ) {
      currentsound = 8;
      print_cur(F("((i<<1)^((i<<1)+(i >> 7)&i>>12))|i >>"), F("(4-(1^7&(i >> 19)))|i>>7"));
    } else if (arduboy.pressed(B_BUTTON) ) {
      currentsound = 10;
      print_cur(F("i*((i>>5|i>>8)>>"), F("(i>>16))"));
    } else {
      currentsound = 4;
      print_cur(F("(int(((sin(i*0.005)"), F("/2.0)+1)*127)"));
    }
  }

  arduboy.display();
}
