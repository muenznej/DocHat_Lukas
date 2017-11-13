int motor[] = {5, 6, 9, 10};

void setup() {
  Serial.begin(9600);
  int i;
  for (i = 0; i < 4; i++) {
    pinMode(motor[i], OUTPUT);
    pinMode(motor[i], OUTPUT);
  }

  int t = 400;
  float s = 0.22;

  for ( int ii = 1; ii < 5; ii++) {

    drive(0, +s);
    delay(t);
    drive(0, 0);

    delay(200);

    drive(0, -s);
    delay(t);
    drive(0, 0);

  }
  drive(0, 0);
}

void loop() {

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
