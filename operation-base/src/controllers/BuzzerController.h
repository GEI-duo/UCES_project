#pragma once

struct Melody {
    int (*notes)[2];
    int size;
};

void setupBuzzer();
void playMelody(const Melody& melody);