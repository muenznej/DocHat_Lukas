#include "pitches.h"

int MAXINT = 0;
boolean hasPlayed = false;
boolean hasDrummed = false;

int motor[] = {5, 6, 9, 10};


#define TERZ_D4 -1
#define TERZ_E4 -2

#define sensorPin A1 // select the input pin for the potentiometer
#define SOUND_PIN 11
#define LED_PIN 8
#define RED_EYES_LED 7


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
//62
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
  pinMode(SOUND_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(RED_EYES_LED,LOW);
  
  for (int i = 0; i < 4; i++) {
    pinMode(motor[i], OUTPUT);
    pinMode(motor[i], OUTPUT);
  }

  int tmp = 0;
  int cc = 0;
  for (int ii = 1; ii <= 10; ii++) {
    cc++    ;
    tmp = tmp + analogRead(sensorPin);
    delay(50);
  }
  MAXINT = tmp / cc;
  Serial.print("Reference Value: ");
  Serial.println(MAXINT, DEC);
  //delay(2000);
}


void loop() {
  int sensorValue = 0; // variable to store the value coming from the sensor
  sensorValue = analogRead(sensorPin);
  float val = float(sensorValue) / float(MAXINT) ;
  Serial.print(sensorValue, DEC);
  Serial.print(", ");
  Serial.println(val, DEC);
  if ( val < 0.6) {
    if (!hasPlayed) {
      Serial.println("Melody started");
      playMelody();
      Serial.println("Melody stopped");
      digitalWrite(LED_PIN, LOW);
      digitalWrite(SOUND_PIN, LOW);
      hasPlayed = true; //for finale
      delay(1000);
      if (!hasDrummed) {
        Serial.println("Drum started");
        playDrums();
        hasDrummed = true;
        Serial.println("Drum stopped");
      }
    }
  }

}
void playDrums() {
  int t = 300;
  float s = 0.6;
  for ( int ii = 1; ii < 11; ii++) {
  digitalWrite(RED_EYES_LED,LOW);
    drive(0, +s);
    drive(1, +s);
    delay(t);
    drive(0, 0);
    drive(1, 0);
    digitalWrite(RED_EYES_LED,HIGH);
  }
  drive(0, 0);
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
  int m = 0;
  // iterate over the NOTEs of the melody:
  //for (int thisNOTE = 0; thisNOTE < sizeof(melody); thisNOTE++) {
  for (int thisNOTE = 0; thisNOTE < 61; thisNOTE++) {
    int NOTEDuration = bps_ms / NOTEDurations[thisNOTE] * 1.8;
    //int NOTEDuration = bps_ms / NOTEDurations[thisNOTE] * 0.2;

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
      if (thisNOTE % 2 == 0) {
        m = 1;
      }
      else {
        m = 0;
      }
      drive(m, 1);
      delay(20);
      drive(m, .27);
      delay(pauseBetweenNOTEs);
      drive(m, 0);
    }
    noTone(SOUND_PIN);
  }
}

void drive(byte motorID, float rotSpeed) {
  byte max_speed = 255;
  byte this_speed = (byte)(max_speed * abs(rotSpeed));
  byte val1 = 0;
  byte val2 = 0;

  if ( rotSpeed < 0 ) {
    val1 = 0;
    val2 = this_speed;
  }
  else if ( rotSpeed > 0 )  {
    val1 = this_speed;
    val2 = 0;
  }

  if (motorID == 0) { // left arm
    analogWrite(motor[0], val1);
    analogWrite(motor[1], val2);
  }
  if (motorID == 1) { // right arm
    analogWrite(motor[2], val1);
    analogWrite(motor[3], val2);
  }
}
