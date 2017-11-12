//KY018 Photo resistor module
 
int sensorPin = A1; // select the input pin for the potentiometer
int ledPin = 7; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  digitalWrite(ledPin, HIGH);
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue, DEC);
}
