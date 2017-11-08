#include "pitches.h"

#define SOUND_PIN 11

#define TERZ_D4 -1
#define TERZ_E4 -2

//int melody[] = {
//  TERZ_E4,
//};
//
//// NOTE durations: 4 = quarter NOTE, 8 = eighth NOTE, etc.:
//float NOTEDurations[] = {
//  8,
//};

int melody[] = {
  //TERZ_E4, TERZ_E4, TERZ_D4, TERZ_E4, NOTE_PAUSE,
  NOTE_E3, NOTE_E3, NOTE_D3, NOTE_E3, NOTE_PAUSE, NOTE_C3,
  NOTE_D3,
  NOTE_E3, NOTE_E3, NOTE_D3, NOTE_E3, NOTE_PAUSE, NOTE_C3,
  NOTE_D3, NOTE_PAUSE, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_PAUSE, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_PAUSE, NOTE_A4, NOTE_G4, NOTE_D4, NOTE_E4,
  NOTE_PAUSE,
  NOTE_PAUSE, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_PAUSE,
  NOTE_A4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_E4,
  NOTE_PAUSE,
  NOTE_PAUSE, NOTE_PAUSE, NOTE_D4, NOTE_E4, NOTE_G4,
  NOTE_D4, NOTE_E4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4,
  NOTE_PAUSE, NOTE_E4, NOTE_E4,
  NOTE_PAUSE
};

// NOTE durations: 4 = quarter NOTE, 8 = eighth NOTE, etc.:
float NOTEDurations[] = {
  8, 8, 8, 8, 4, 4,
  1,
  8, 8, 8, 8, 4, 4,
  2, 4, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8 / 1, 8 / 7,
  2,
  4 / 3, 8, 8,
  8, 8, 8, 8, 2,
  8, 8, 8, 8, 4, 8, 8 / 5,
  2,
  2, 8, 8, 8, 4,
  8, 8, 4, 8, 8, 8 / 5,
  4, 8, 8 / 5,
  2
};

float bps = 106 / 60;
float bps_ms = bps * 1000;

void setup() {
  pinMode(SOUND_PIN, OUTPUT);

  // // we will use the FALLING state from PB2 where a IR Lightsensor is attatched
  // attachInterrupt(digitalPinToInterrupt(2), runMelody, FALLING ); // use int0 = PB2 = pin 7


  // iterate over the NOTEs of the melody:
  for (int thisNOTE = 0; thisNOTE < sizeof(melody); thisNOTE++) {
    int NOTEDuration = bps_ms / NOTEDurations[thisNOTE] * 1.8;

    // check for TERZ_D4, quickly alter that tone
    if (melody[thisNOTE] == -1) {
      playTerz(NOTE_G4, NOTE_E4, NOTEDuration);
    }
    // check for TERZ_E4
    if (melody[thisNOTE] == -2) {
      playTerz(NOTE_F4, NOTE_D4, NOTEDuration);
    }
    else {
      tone(SOUND_PIN, melody[thisNOTE], NOTEDuration);
      int pauseBetweenNOTEs = NOTEDuration ;
      delay(pauseBetweenNOTEs);
    }
    noTone(SOUND_PIN);
  }
}


void loop() {
  noTone(SOUND_PIN);
}

void playTerz( int a, int b, int NOTEDuration ) {
  int mydevide = 8;
  int pauseBetweenNOTEs = NOTEDuration / 2 / mydevide;
  for (int ii = 1; ii <= mydevide ; ii++) {
    tone(SOUND_PIN, a, NOTEDuration  / mydevide / 2);
    delay(100);
    noTone(SOUND_PIN);
    //delay(pauseBetweenNOTEs);
    tone(SOUND_PIN, b, NOTEDuration / mydevide / 2);
    
    delay(100);
    noTone(SOUND_PIN);
    //delay(pauseBetweenNOTEs);
  }
}

