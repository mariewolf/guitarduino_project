#ifndef TICKFUNCS_H
#define TICKFUNCS_H

#include "binary.h"
#include "Arduino.h"

int buttons[] = {A3, A4, A5, A7, -1};
int check_button_press(int pin);

int count = 0;
bool correct_press = true;
bool song_playing = false;
bool ready_to_play = false;

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

//int row_1_pin = 11, row_2_pin = 13, row_3_pin = 12, row_4_pin = 9, row_5_pin = 4, row_6_pin = 37, row_7_pin = 6, row_8_pin = 36;
//int col_1_pin = 8, col_2_pin = 2, col_3_pin = 3, col_4_pin = 10, col_5_pin = 5;

#endif