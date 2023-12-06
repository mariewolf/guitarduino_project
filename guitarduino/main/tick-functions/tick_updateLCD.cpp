#ifndef TICK_UPDATELCD_CPP
#define TICK_UPDATELCD_CPP

#include "TickFuncs.h"
#include <LiquidCrystal.h>

const int rs = 45, en = 44, d4 = 47, d5 = 46, d6 = 49, d7 = 48;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
enum LCD_STATES {LCD_start, LCD_SONG_SELECTION, LCD_READY, LCD_SET, LCD_GO, LCD_GAME_OVER};
int Tick_UPDATE_LCD(int state) {
    lcd.clear();
    switch(state) {
        case LCD_start:
            state = LCD_SONG_SELECTION;
            break;
        case LCD_SONG_SELECTION:
            if (game_over) {
                state = LCD_SONG_SELECTION;
            }
            else {
                state = LCD_READY;
            }
            break;
        case LCD_READY:
            state = LCD_SET;
            break;
        case LCD_SET:
            state = LCD_GO;
            break;
        case LCD_GO:
            ready_to_play = true;
            if (song_playing)
                state = LCD_GO;
            else
                state = LCD_GAME_OVER;
            break;
        case LCD_GAME_OVER:
            if (!digitalRead(A10)) {
                ready_to_play = false;
                game_over = true;
                state = LCD_SONG_SELECTION;
            }
            else {
                state = LCD_GAME_OVER;
            }
            break;
        default:
            state = LCD_start;
            break;
    }
    switch(state) {
        case LCD_start:
            break;
        case LCD_SONG_SELECTION:
            lcd.setCursor(0, 0);
            lcd.print("Song selected:");
            lcd.setCursor(0, 1);
            lcd.print("<-");
            lcd.setCursor(5, 1);
            lcd.print(song_names[selectedSong]); //print song name
            lcd.setCursor(14, 1);
            lcd.print("->");
            break;
        case LCD_READY:
            lcd.setCursor(0, 0);
            lcd.print("Ready");

            break;
        case LCD_SET:
            lcd.setCursor(0, 0);
            lcd.print("Set");
            break;
        case LCD_GO:
            lcd.setCursor(0, 0);
            lcd.print("Go!");
            break;
        case LCD_GAME_OVER:
            lcd.setCursor(0, 0);
            lcd.print("Game Over");
            break;
        default:
            break;
    }
    return state;
}

#endif