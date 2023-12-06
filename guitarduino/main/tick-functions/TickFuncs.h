#ifndef TICKFUNCS_CPP
#define TICKFUNCS_CPP

#include "binary.h"
#include "Arduino.h"
#include "../SongArrays.h"

int buttons[] = {A3, A4, A5, A7, -1};
int check_button_press(int pin);

int count = 0;
bool correct_press = true;

bool playing = false;
bool ready_to_play = false;

int selectedSong = 0;
int* songNotes = song_0_notes;
int* songRythm = song_0_rythm;
int songSize = 0;

void Test() {
        //int b1 = digitalRead(A3);
        int b1 = check_button_press(3);
        
        //int b1 = digitalRead(check_button_press(buttons[0]));
        //int b2 = digitalRead(check_button_press(buttons[1]));
        //int b3 = digitalRead(check_button_press(buttons[2]));
        //int b4 = digitalRead(check_button_press(buttons[3]));
        Serial.print(b1);
        // Serial.print("Button 1: "); Serial.print(b1); Serial.print("\t");
        // Serial.print("Button 2: "); Serial.print(b2); Serial.print("\t");
        // Serial.print("Button 3: "); Serial.print(b3); Serial.print("\t");
        // Serial.print("Button 4: "); Serial.print(b4); Serial.print("\t");
        Serial.print("\n");
}

#endif