
#include "pitches.h"

const int speakerPin = 8;
const int potPin = A0;
const int buttonPin = 2;

// C major scale across two octaves
int notes[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_A4, NOTE_B4,
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5,
  NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6
};

const int numberOfNotes = sizeof(notes) / sizeof(notes[0]);

unsigned long lastGlitchTime = 0;

int glitchPitch = NOTE_C4;
bool glitchSoundOn = true;

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  randomSeed(analogRead(A1));
}

void loop() {
  int potValue = analogRead(potPin);

  // Select a note with the potentiometer
  int noteIndex = map(potValue, 0, 1024, 0, numberOfNotes);
  noteIndex = constrain(noteIndex, 0, numberOfNotes - 1);

  int normalPitch = notes[noteIndex];

  // Higher potentiometer value = faster glitches
  int glitchSpeed = map(potValue, 0, 1023, 250, 25);

  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {

    if (millis() - lastGlitchTime >= glitchSpeed) {
      lastGlitchTime = millis();

      // Select a random glitch pattern
      int glitchType = random(0, 3);

      if (glitchType == 0) {
        // Pattern 1: Jump between musical notes
        int randomIndex = noteIndex + random(-5, 6);
        randomIndex = constrain(randomIndex, 0, numberOfNotes - 1);

        glitchPitch = notes[randomIndex];
        glitchSoundOn = true;

      } else if (glitchType == 1) {
        // Pattern 2: Stutter
        glitchPitch = normalPitch;
        glitchSoundOn = !glitchSoundOn;

      } else {
        // Pattern 3: Dropout
        glitchSoundOn = false;
      }
    }

    if (glitchSoundOn) {
      tone(speakerPin, glitchPitch);
    } else {
      noTone(speakerPin);
    }

  } else {
    // Normal synthesizer mode
    tone(speakerPin, normalPitch);
  }
}
