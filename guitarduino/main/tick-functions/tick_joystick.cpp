#ifndef TICK_JOYSTICK_CPP
#define TICK_JOYSTICK_CPP

#include "TickFuncs.h"

const int joystick_button = A10, joystick_x = A2;

enum JOYSTICK_STATES {JOYSTICK_wait, JOYSTICK_left, JOYSTICK_right, JOYSTICK_pressed};
int Tick_JOYSTICK(int state) {

    int x = analogRead(joystick_x); //read x axis of joystick
    x = map(x, 0, 1023, 0, 2); 
    int button = digitalRead(joystick_button);
    static int num_songs = sizeof(song_names)/sizeof(song_names[0]);

    switch(state) {
        case JOYSTICK_wait:
            if (x == 0) {
                state = JOYSTICK_left;
                }
            else if (x == 2) {
                state = JOYSTICK_right;
            }
            else if (button == 0) {
                state = JOYSTICK_pressed;
                if (selectedSong == 0) {
                    songNotes = song_0_notes;
                    songRythm = song_0_rythm;
                    songSize = sizeof(song_0_notes)/sizeof(song_0_notes[0]);
                }
                else if (selectedSong == 1) {
                    songNotes = song_1_notes;
                    songRythm = song_1_rythm;
                    songSize = sizeof(song_1_notes)/sizeof(song_1_notes[0]);
                }
                else if (selectedSong == 2) {
                    songNotes = song_2_notes;
                    songRythm = song_2_rythm;
                    songSize = sizeof(song_2_notes)/sizeof(song_2_notes[0]);
                }
                
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
                if (ready_to_play) {
                    state = JOYSTICK_wait;
                }
                else {
                    state = JOYSTICK_pressed;
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
                selectedSong = num_songs - 1;
            }
            break;
        case JOYSTICK_right:
            if (selectedSong < num_songs - 1) {
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

    // Serial.print("button: ");
    // Serial.print(button);
    // Serial.print("\tx: ");
    // Serial.print(x);
    // Serial.print("\tselected song: ");
    // Serial.print(selectedSong);
    // Serial.print("\tnum songs: ");
    // Serial.print(num_songs);
    // Serial.print("\n");

    return state;
    

}

#endif