#include "pitches.h"

#define SOUND_PIN 0

#define TERZ_D4 -1
#define TERZ_E4 -2

int melody[] = {
  TERZ_E4, TERZ_E4, TERZ_D4, TERZ_E4, NOTE_PAUSE,
  TERZ_D4,
  TERZ_E4, TERZ_E4, TERZ_D4, TERZ_E4, NOTE_PAUSE,
  TERZ_D4,
  TERZ_E4, TERZ_E4, TERZ_D4, TERZ_E4, NOTE_PAUSE,
  TERZ_D4,
  TERZ_E4, TERZ_E4, TERZ_D4, TERZ_E4, NOTE_PAUSE,
  TERZ_D4, NOTE_PAUSE, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_PAUSE, NOTE_GS4, NOTE_A4, NOTE_G4,
  NOTE_PAUSE, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_E4,
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
  8, 8, 8, 8, 2,
  1,
  8, 8, 8, 8, 2,
  1,
  8, 8, 8, 8, 2,
  1,
  8, 8, 8, 8, 2,
  2, 4, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8 / 3, 8 / 6,
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





void setup() {
  pinMode(SOUND_PIN, OUTPUT);
}

//int TERZ_E4[] = {
//  NOTE_G4, NOTE_E4
//};
//
//int TERZ_D4[] = {
//  NOTE_F4, NOTE_D4
//};

void loop() {
  // // we will use the FALLING state from PB2 where a IR Lightsensor is attatched
  // attachInterrupt(digitalPinToInterrupt(2), runMelody, FALLING ); // use int0 = PB2 = pin 7
  int bps = 106 / 60 / 4;
  int bps_ms = bps * 1000;

  // iterate over the NOTEs of the melody:
  for (int thisNOTE = 0; thisNOTE < sizeof(melody); thisNOTE++) {
    int NOTEDuration = bps_ms / NOTEDurations[thisNOTE];
    // check for TERZ_D4, quickly alter that tone
    if (melody[thisNOTE] == -1) {
      int mydevide = 8;
      int pauseBetweenNOTEs = NOTEDuration / mydevide / 2 * 1.30;
      for (int ii = 1; ii <= mydevide / 2; ii++) {
        tone(SOUND_PIN, NOTE_G4, NOTEDuration / mydevide);
        delay(pauseBetweenNOTEs);
        tone(SOUND_PIN, NOTE_E4, NOTEDuration / mydevide);
        delay(pauseBetweenNOTEs);
      }
    }
    // check for TERZ_E4
    if (melody[thisNOTE] == -2) {
      int mydevide = 8;
      int pauseBetweenNOTEs = NOTEDuration / mydevide / 2 * 1.30;
      for (int ii = 1; ii <= mydevide / 2; ii++) {
        tone(SOUND_PIN, NOTE_F4, NOTEDuration / mydevide);
        delay(pauseBetweenNOTEs);
        tone(SOUND_PIN, NOTE_D4, NOTEDuration / mydevide);
        delay(pauseBetweenNOTEs);
      }
    }
    else {
      tone(SOUND_PIN, melody[thisNOTE], NOTEDuration);
      int pauseBetweenNOTEs = NOTEDuration * 1.30;
      delay(pauseBetweenNOTEs);
    }
    noTone(SOUND_PIN);
  }
}
