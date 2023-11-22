#include "SongArrays.h"
#include "LedControl.h"
#include "binary.h"

int count = 0;
bool correct_press = true;

void Test() {
        Serial.print("\nTest");
}

enum SVNSEG_STATES {SVNSEG_start, display_three, display_two, display_one, display_zero};
int pin_A=29, pin_B=30, pin_C=27, pin_D=24, pin_E=25, pin_F=28, pin_G=26;
int pin_D1=34, pin_D2=35, pin_D3=33, pin_D4=32;

int display_pins[] = {pin_A, pin_B, pin_C, pin_D, pin_E, pin_F, pin_G, pin_D4, pin_D3, pin_D2, pin_D1};
int Tick_SVNSEG(int state) {
    int count_parse = count;
    int thousands = count_parse / 1000; count_parse %= 1000;
    int hundreds = count_parse / 100; count_parse %= 100;
    int tens = count_parse / 10; count_parse %= 10;
    int ones = count_parse;

    static char pin_to_display_on = display_pins[10];
    int last_displayed_pin = pin_to_display_on;
    int num_to_display = 0;

    switch(state) {
        case SVNSEG_start:
            state = display_three;
            break;
        case display_three:
            state = display_two;
            break;
        case display_two:
            state = display_one;
            break;
        case display_one:
            state = display_zero;
            break;
        case display_zero:
            state = display_three;
            break;
        default:
            state = SVNSEG_start;
            break;
    }
    switch(state) {
        case SVNSEG_start:
            break;
        case display_three:
            pin_to_display_on = display_pins[10];
            num_to_display = ones;
            break;
        case display_two:
            pin_to_display_on = display_pins[9];
            num_to_display = tens;
            break;
        case display_one:
            pin_to_display_on = display_pins[8];
            num_to_display = hundreds;
            break;
        case display_zero:
            pin_to_display_on = display_pins[7];
            num_to_display = thousands;
            break;
        default:
            break;
    }

    digitalWrite(last_displayed_pin, HIGH);
    //digitalWrite(pin_to_display_on, HIGH);
    unsigned char encodeInt[10] = {
        // 0     1     2     3     4     5     6     7     8     9
        0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67,
    };
    for (int k = 0; k < 7; ++k) {
        digitalWrite(display_pins[k], encodeInt[num_to_display] & (1 << k));
    }
    // Turn on the digit again
    digitalWrite(pin_to_display_on, LOW);
    return state;
}

int buzzer_pin = A0;
int buzzer2_pin = A8;
enum BUZZER_STATES {buzz_start, buzz_on, buzz_off};

int Tick_BUZZER(int state) {
    static int where_to_start = 0;
    switch(state) {
        case buzz_start:
            state = buzz_on;
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
            noTone(buzzer_pin);
            noTone(buzzer2_pin);
            break;
        default:
            break;
    }
    return state;
}

int row_1_pin = 11, row_2_pin = 13, row_3_pin = 12, row_4_pin = 9, row_5_pin = 4, row_6_pin = 37, row_7_pin = 6, row_8_pin = 36;
int col_1_pin = 8, col_2_pin = 2, col_3_pin = 3, col_4_pin = 10, col_5_pin = 5;
int buttons[] = {A1, A2, A3, A4, A5, -1};

void display_on_LED_matrix(int row, int col);

byte next_row_in = B00110011;
byte LEDrows[16] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
                B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};

enum LED_ROW_CONTROL {LED_ROW_CONTROL_start, shift_down, leds_off};
//int LED_ROWS[] = {row_1_pin, row_2_pin, row_3_pin, row_4_pin, row_5_pin, row_6_pin, row_7_pin, row_8_pin};
//int LED_COLS[] = {col_1_pin, col_2_pin, col_3_pin, col_4_pin, col_5_pin};
int latchPin = 39;
int clockPin = 41;
int dataPin = 37;

LedControl lc=LedControl(dataPin,clockPin,latchPin,2);

int check_button_press(int pin);

int Tick_LED_ROW_CONTROL(int state) {
    static int where_to_start = 0;

    static int corr_button = 2;
    // static int last_corr_button = corr_button;
    // for (int i = 0; i < 5; i++) {
    //     if (eighth_row[i]) {
    //         corr_button = i;
    //         break;
    //     }
    // }
    // if (corr_button != last_corr_button) {
    //     last_corr_button = corr_button;
        if (corr_button && check_button_press(0) ||
            (corr_button == 1 && check_button_press(1)) ||
            (corr_button == 2 && check_button_press(2)) ||
            (corr_button == 3 && check_button_press(3)) ||
            (corr_button == 4 && check_button_press(4))) //{
             count +=0;
    //         correct_press = true;
    //         }
    // }

    int row_parse = tetris_rythm[where_to_start];
    // next_row_in[0] = row_parse / 10000; row_parse %= 10000;
    // next_row_in[1] = row_parse / 1000; row_parse %= 1000;
    // next_row_in[2] = row_parse / 100; row_parse %= 100;
    // next_row_in[3] = row_parse / 10; row_parse %= 10;
    // next_row_in[4] = row_parse;
    next_row_in = row_parse;


    switch(state) {
        case LED_ROW_CONTROL_start:
            state = shift_down;
            break;
        case shift_down:
            state = shift_down;
            break;
        case leds_off:
            state = leds_off;
            break;
        default:
            state = LED_ROW_CONTROL_start;
            break;
    }
    switch(state) {
        case LED_ROW_CONTROL_start:
            break;
        case shift_down:
                for (int i = 15; i > 0; i--) {
                    LEDrows[i] = LEDrows[i-1];
                }
                // for (int i = 0; i < 5; i++)
                //    first_row[i] = next_row_in[i];
                LEDrows[0] = next_row_in;
                where_to_start++;

                    // Serial.print(next_row_in[0]);
                    // Serial.print(next_row_in[1]);
                    // Serial.print(next_row_in[2]);
                    // Serial.print(next_row_in[3]);
                    // Serial.print(next_row_in[4]);
                    // Serial.print("\n");


            break;
        case leds_off:
            // for (int i = 0; i < 5; i++)
                   LEDrows[0] = B00000000;
        default:
            break;
    }
    if (where_to_start == sizeof(tetris_rythm)/sizeof(tetris_rythm[0])) {
        state = leds_off;
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

// enum LED_MATRIX_STATES {LED_MATRIX_start, LED_ROW_1, LED_ROW_2, LED_ROW_3, LED_ROW_4, LED_ROW_5, LED_ROW_6, LED_ROW_7, LED_ROW_8};
// int Tick_LED_MATRIX(int state) {
//     for (auto x : LED_ROWS)
//       digitalWrite(x, LOW);
  
//     for (auto x : LED_COLS)
//       digitalWrite(x, HIGH);

//     switch(state) {
//         case LED_MATRIX_start:
//             state = LED_ROW_1;
//             break;
//         case LED_ROW_1:
//             state = LED_ROW_2;
//             break;
//         case LED_ROW_2:
//             state = LED_ROW_3;
//             break;
//         case LED_ROW_3:
//             state = LED_ROW_4;
//             break;
//         case LED_ROW_4:
//             state = LED_ROW_5;
//             break;
//         case LED_ROW_5:
//             state = LED_ROW_6;
//             break;
//         case LED_ROW_6:
//             state = LED_ROW_7;
//             break;
//         case LED_ROW_7:
//             state = LED_ROW_8;
//             break;
//         case LED_ROW_8:
//             state = LED_ROW_1;
//             break;
//         default:
//             state = LED_MATRIX_start;
//             break;
//     }
//     switch(state) {
//         case LED_MATRIX_start:
//             break;
//         case LED_ROW_1:
//             for (int i = 0; i < 5; i++) {
//                 if (first_row[i])
//                     display_on_LED_matrix(1, i);
//             }
//             break;
//         case LED_ROW_2:
//             for (int i = 0; i < 5; i++) {
//                 if (second_row[i])
//                     display_on_LED_matrix(2, i);
//             }
//             break;
//         case LED_ROW_3:
//             for (int i = 0; i < 5; i++) {
//                 if (third_row[i])
//                     display_on_LED_matrix(3, i);
//             }
//             break;
//         case LED_ROW_4:
//             for (int i = 0; i < 5; i++) {
//                 if (fourth_row[i])
//                     display_on_LED_matrix(4, i);
//             }
//             break;
//         case LED_ROW_5:
//             for (int i = 0; i < 5; i++) {
//                 if (fifth_row[i])
//                     display_on_LED_matrix(5, i);
//             }
//             break;
//         case LED_ROW_6:
//             for (int i = 0; i < 5; i++) {
//                 if (sixth_row[i])
//                     display_on_LED_matrix(6, i);
//             }
//             break;
//         case LED_ROW_7:
//             for (int i = 0; i < 5; i++) {
//                 if (seventh_row[i])
//                     display_on_LED_matrix(7, i);
//             }
//             break;
//         case LED_ROW_8:
//             for (int i = 0; i < 5; i++) {
//                 if (eighth_row[i])
//                     display_on_LED_matrix(8, i);
//             }
//             break;
            
//         default:
//             break;
//     }
//     return state;
// }

int check_button_press(int pin) {
    if (digitalRead(buttons[pin]) == HIGH)
        return 1;
    return 0;
}

int other_output_pins[] = {buzzer_pin, buzzer2_pin, row_6_pin, row_8_pin, col_2_pin, col_3_pin, row_5_pin, col_5_pin, row_7_pin, row_2_pin, col_1_pin, row_4_pin, col_4_pin, row_1_pin, row_3_pin};

// void display_on_LED_matrix(int row, int col) {
//     digitalWrite(LED_ROWS[row-1], HIGH);
//     digitalWrite(LED_COLS[col], LOW);
// }