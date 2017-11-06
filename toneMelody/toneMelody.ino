#include "pitches.h"
int melody[] = {
  TERZ_E4, TERZ_E4, TERZ_D4, TERZ_E4, NOTE_PAUSE,
  TERZ_D4,
  TERZ_E4, TERZ_E4, TERZ_D4, TERZ_E4, NOTE_PAUSE,
  TERZ_D4,
  TERZ_E4, TERZ_E4, TERZ_D4, TERZ_E4, NOTE_PAUSE,
  TERZ_D4,
  TERZ_E4, TERZ_E4, TERZ_D4, TERZ_E4, NOTE_PAUSE,
  TERZ_D4, NOTE_PAUSE, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_PAUSE, NOTE_H4, NOTE_A4, NOTE_G4,
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
  8, 8, 8, 8/3, 8/6,
  2, 
  4/3, 8, 8,
  8, 8, 8, 8, 2,
  8, 8, 8, 8, 4, 8, 8/5,
  2,
  2, 8, 8, 8, 4,
  8, 8, 4, 8, 8, 8/5,
  4, 8, 8/5,
  2
};

int TERZ_E4[] = {
  NOTE_G4, NOTE_E4
};

int TERZ_D4[] = {
  NOTE_F4, NOTE_D4
};
void setup() {
  // iterate over the NOTEs of the melody:
  for (int thisNOTE = 0; thisNOTE < 8; thisNOTE++) {

    // to calculate the NOTE duration, take one second divided by the NOTE type.
    //e.g. quarter NOTE = 1000 / 4, eighth NOTE = 1000/8, etc.
    int bpm = 106 / 60 / 4 * 1000;

    int NOTEDuration = bpm / NOTEDurations[thisNOTE];
    tone(8, melody[thisNOTE], NOTEDuration);

    // to distinguish the NOTEs, set a minimum time between them.
    // the NOTE's duration + 30% seems to work well:
    int pauseBetweenNOTEs = NOTEDuration * 1.30;
    delay(pauseBetweenNOTEs);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
  // no need to repeat the melody.
}
