#include "pitches.h"

int MAXINT = 0;
boolean hasPlayed = false;
#define TERZ_D4 -1
#define TERZ_E4 -2

#define sensorPin A1 // select the input pin for the potentiometer
#define ledPin 7 // select the pin for the LED
#define SOUND_PIN 11

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
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  pinMode(SOUND_PIN, OUTPUT);

  int tmp = 0;
  int cc = 0;
  for (int ii = 1; ii <= 10; ii++) {
    cc++    ;
    tmp = tmp + analogRead(sensorPin);
    delay(50);
  }
  MAXINT = tmp / cc;
  Serial.println(MAXINT, DEC);
}


void loop() {
  int sensorValue = 0; // variable to store the value coming from the sensor

  sensorValue = analogRead(sensorPin);
  if ((sensorValue / MAXINT) < 0.5) {
    if (!hasPlayed) {
      playMelody();
      //hasPlayed = true; for finale
    }
    Serial.println(sensorValue, DEC);
  }

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

void playMelody( ) {
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

