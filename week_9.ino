void setup() {
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  // Read the potentiometer
  int energy = analogRead(A2);

  // Control yellow LED brightness
  analogWrite(9, energy / 4);

  // Read the push button
  int buttonState = digitalRead(2);

  // Activate ability only when energy is high enough
  if (buttonState == HIGH && energy > 500) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}
