#ifndef TICK_JOYSTICK_CPP
#define TICK_JOYSTICK_CPP

#include "TickFuncs.h"

const int joystick_button = -1, joystick_x = -2, joystick_y = -3; //FIXME: change these to the correct pins

enum JOYSTICK_STATES {JOYSTICK_wait, JOYSTICK_left, JOYSTICK_right, JOYSTICK_pressed};
int Tick_JOYSTICK(int state) {

    int x = analogRead(joystick_x);
    int y = analogRead(joystick_y);
    int button = digitalRead(joystick_button);

    switch(state) {
        case JOYSTICK_wait:
            if (x < 1000) {
                    state = JOYSTICK_left;
                }
            else if (x > 3000) {
                state = JOYSTICK_right;
            }
            else if (button == 0) {
                game_over = false;
                state = JOYSTICK_pressed;
            }
            else {
                state = JOYSTICK_wait;
            }
            break;
        case JOYSTICK_left:
                state = JOYSTICK_wait;
            break;
        case JOYSTICK_right:
                state = JOYSTICK_wait;
            break;
        case JOYSTICK_pressed:
                if (game_over) {
                    state = JOYSTICK_wait;
                }
                else {
                    state = JOYSTICK_pressed;
                    if (selectedSong == 0) {
                        songNotes = song_0_notes;
                        songRythm = song_0_rythm;
                    }
                    else if (selectedSong == 1) {
                        songNotes = song_1_notes;
                        songRythm = song_1_rythm;
                    }
                    else if (selectedSong == 2) {
                        songNotes = song_2_notes;
                        songRythm = song_2_rythm;
                    }
                }
            break;
        default:
            state = JOYSTICK_wait;
            break;
    }
    switch(state) {
        case JOYSTICK_wait:
            break;
        case JOYSTICK_left:
            if (selectedSong > 0) {
                selectedSong--;
            }
            else {
                selectedSong = sizeof(song_names)/sizeof(song_names[0]) - 1;
            }
            break;
        case JOYSTICK_right:
            if (selectedSong < sizeof(song_names)/sizeof(song_names[0]) - 1) {
                selectedSong++;
            }
            else {
                selectedSong = 0;
            }
            break;
        case JOYSTICK_pressed:
            break;
        default:
            state = JOYSTICK_wait;
            break;
    }
    switch(state) {
        case JOYSTICK_wait:
            break;
        case JOYSTICK_left:
            if (selectedSong > 0) {
                selectedSong--;
            }
            break;
        case JOYSTICK_right:
            if (selectedSong < 3) {
                selectedSong++;
            }
    }
}

#endif