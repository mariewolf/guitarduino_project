#ifndef TICK_BUZZER_H
#define TICK_BUZZER_H

#include "TickFuncs.h"
#include "../SongArrays.h"

int buzzer_pin = A0;
int buzzer2_pin = A8;
int buzzer_pins[] = {buzzer_pin, buzzer2_pin};
enum BUZZER_STATES {buzz_start, buzz_on, buzz_off};

int Tick_BUZZER(int state) {
    static int where_to_start = 0;
    switch(state) {
        case buzz_start:
            if (ready_to_play) {
                state = buzz_on;
            }
            else {
                state = buzz_start;
            }
            break;
        case buzz_on:
            state = buzz_on;
            break;
        case buzz_off:
            state = buzz_off;
            break;
        default:
            state = buzz_start;
            break;
    }
    switch(state) {
        case buzz_start:
            break;
        case buzz_on:
            song_playing = true;
            if (correct_press) {
              tone(buzzer_pin, tetris_buzzer_1[where_to_start]);
              tone(buzzer2_pin, tetris_buzzer_2[where_to_start]);
            }
            else {
              noTone(buzzer_pin);
              noTone(buzzer2_pin);
            }
            where_to_start++;
            if (where_to_start == sizeof(tetris_buzzer_1)/sizeof(tetris_buzzer_1[0]))
                state = buzz_off;
            break;
        case buzz_off:
            song_playing = false;
            noTone(buzzer_pin);
            noTone(buzzer2_pin);
            break;
        default:
            break;
    }
    return state;
}

#endif