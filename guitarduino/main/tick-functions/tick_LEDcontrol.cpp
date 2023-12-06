#ifndef TICK_LED_CONTROL_CPP
#define TICK_LED_CONTROL_CPP

#include "TickFuncs.h"
#include "../SongArrays.h"
#include "LedControl.cpp"
#include "LedControl.h"


byte next_row_in = B00110011;
byte LEDrows[16] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
                B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};

enum LED_ROW_CONTROL {LED_ROW_CONTROL_start, shift_down, leds_off};
int latchPin = 12;
int clockPin = 11;
int dataPin = 13;

LedControl lc=LedControl(dataPin,clockPin,latchPin,2);


int Tick_LED_ROW_CONTROL(int state) {
    static int where_to_start = 0;

    static int corr_button = 2;
    static int last_corr_button = corr_button;
    if (LEDrows[15] == B00000011)
        corr_button = 3;
    else if (LEDrows[15] == B00001100)
        corr_button = 2;
    else if (LEDrows[15] == B00110000)
        corr_button = 1;
    else if (LEDrows[15] == B11000000)
        corr_button = 0;
    else if (LEDrows[15] == B00000000)
        corr_button = 4;
    if (corr_button != last_corr_button) {
        last_corr_button = corr_button;
        if (corr_button == 0 && check_button_press(0) ||
            (corr_button == 1 && check_button_press(1)) ||
            (corr_button == 2 && check_button_press(2)) ||
            (corr_button == 3 && check_button_press(3))) {
             count +=5;
            correct_press = true;
            }
            // else { // setting the correct press to false will make the buzzer not play
            //     correct_press = false;
            // }
    }

    int row_parse = songRythm[where_to_start];
    next_row_in = row_parse;


    switch(state) {
        case LED_ROW_CONTROL_start:
            if (playing) {
                state = shift_down;
            }
            else {
                state = LED_ROW_CONTROL_start;
            }
            //Serial.println("LED ROW CONTROL START");
            break;
        case shift_down:
            state = shift_down;
            //Serial.println("LED ROW CONTROL SHIFT DOWN");
            break;

        case leds_off:
            state = leds_off;
            //Serial.println("LED ROW CONTROL LEDS OFF");
            break;

        default:
            state = LED_ROW_CONTROL_start;
            //Serial.println("LED ROW CONTROL DEFAULT");
            break;
    }
    switch(state) {
        case LED_ROW_CONTROL_start:
            break;
        case shift_down:
                for (int i = 15; i > 0; i--) {
                    LEDrows[i] = LEDrows[i-1];
                }
                LEDrows[0] = next_row_in;
                where_to_start++;
            break;
        case leds_off:
                LEDrows[0] = B00000000;
        default:
            break;
    }
    if (where_to_start > (songSize - 1)) {
        where_to_start = 0;
        lc.setRow(0,0,B00000000);
        byte LEDrows[16] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
                B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};
        state = LED_ROW_CONTROL_start;
        //where_to_start = 0;
    }

    lc.setRow(0,0,LEDrows[0]);
    lc.setRow(0,1,LEDrows[1]);
    lc.setRow(0,2,LEDrows[2]);
    lc.setRow(0,3,LEDrows[3]);
    lc.setRow(0,4,LEDrows[4]);
    lc.setRow(0,5,LEDrows[5]);
    lc.setRow(0,6,LEDrows[6]);
    lc.setRow(0,7,LEDrows[7]);
    lc.setRow(1,0,LEDrows[8]);
    lc.setRow(1,1,LEDrows[9]);
    lc.setRow(1,2,LEDrows[10]);
    lc.setRow(1,3,LEDrows[11]);
    lc.setRow(1,4,LEDrows[12]);
    lc.setRow(1,5,LEDrows[13]);
    //lc.setRow(1,6,LEDrows[14]);
    lc.setRow(1,6,B11111111);
    lc.setRow(1,7,LEDrows[15]);


    return state;
}


int check_button_press(int pin) {
    if (pin == -1)
        return 0;
    if (digitalRead(buttons[pin]) != 0)
        return 0;
    return 1;
}

#endif