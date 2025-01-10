#include <Arduino.h>
#include <ezBuzzer.h>

#include "pitches.h"

#define BUZZER_PIN 33

#define DO 523
#define RE 587
#define MI 659
#define FA 698
#define SOL 784
#define LA 880
#define SI 988
#define RE2 1175
#define DO2 1062
#define DoS 554
#define RES 622
#define FAS 740
#define SOLS 830
#define FAS2 1479
#define a 1000
#define b 500

int melody[] = {SOL, RE,  SI,  SOL, RE2, DO2, SI,  LA,  SOL, SOL, FAS,
                MI,  RE,  SOL, LA,  SI,  RE2, DO2, SI,  LA,  SOL, RE2,
                RE2, SI,  RE2, DO2, LA,  DO2, SI,  SOL, SI,  LA,  RE,
                MI,  FAS, SOL, LA,  SI,  DO2, RE2, DO2, SI,  LA,  SOL};

int noteDurations[] = {a, a,   a,   b, b,    b,   b, b,   b,   b, b,
                       b, b,   a,   a, 1500, b,   b, b,   b,   b, 2000,
                       a, 250, 250, a, 250,  250, a, 250, 250, b, b,
                       b, b,   a,   a, 250,  250, b, b,   a,   a, 2000};

int noteLength;

void playMelody() {
  for (int i = 0; i < noteLength; i++) {
    int duration = noteDurations[i];
    if (melody[i] == 0) {
      delay(duration);
    } else {
      tone(BUZZER_PIN, melody[i], duration);
      delay(duration);
    }
    delay(50);
  }
}

void setup() {
  noteLength = sizeof(melody) / sizeof(melody[0]);
}

void loop() {
  playMelody();
  delay(1000);
}
