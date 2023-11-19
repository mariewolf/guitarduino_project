using namespace std;

int count = 0;

void Test() {
        Serial.print("\nTest");
}

enum SVNSEG_STATES {SVNSEG_start, display_three, display_two, display_one, display_zero};
int pin_A=29, pin_B=30, pin_C=27, pin_D=24, pin_E=25, pin_F=28, pin_G=26;
int pin_D1=34, pin_D2=35, pin_D3=33, pin_D4=32;

int display_pins[] = {pin_A, pin_B, pin_C, pin_D, pin_E, pin_F, pin_G, pin_D4, pin_D3, pin_D2, pin_D1};
Tick_SVNSEG(int state) {
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
enum BUZZER_STATES {buzz_start, buzz_on, buzz_off};
int C5 = 523, D5 = 587, E5 = 659, F5 = 698, G5 = 784, note_A5 = 880, B5 = 988;
int C6 = 1047, D6 = 1175, E6 = 1319, F6 = 1397, G6 = 1568, note_A6 = 1760, B6 = 1976;
int C7 = 2093, D7 = 2349, E7 = 2637, F7 = 2794, G7 = 3136, note_A7 = 3520, B7 = 3951;
int C8 = 4186, D8 = 4699, E8 = 5274, F8 = 5588, G8 = 6272, note_A8 = 7040, B8 = 7902;

Tick_BUZZER(int state) {
    switch(state) {
        case buzz_start:
            state = buzz_on;
            break;
        case buzz_on:
            state = buzz_off;
            break;
        case buzz_off:
            state = buzz_on;
            break;
        default:
            state = buzz_start;
            break;
    }
    switch(state) {
        case buzz_start:
            break;
        case buzz_on:
            tone(buzzer_pin, B6);
            break;
        case buzz_off:
            noTone(buzzer_pin);
            break;
        default:
            break;
    }
    return state;
}

int row_1_pin = 11, row_2_pin = 7, row_3_pin = 12, row_4_pin = 9, row_5_pin = 4, row_6_pin = 37, row_7_pin = 6, row_8_pin = 36;
int col_1_pin = 8, col_2_pin = 2, col_3_pin = 3, col_4_pin = 10, col_5_pin = 5;

void display_on_LED_matrix(int row, int col);
int next_row_in[] = {0,0,0,0,0};
int first_row[] =   {1,1,1,1,1};
int second_row[] =  {0,0,0,0,0};
int third_row[] =   {0,1,0,0,0};
int fourth_row[] =  {0,0,0,0,0};
int fifth_row[] =   {0,0,0,1,1};
int sixth_row[] =   {0,0,0,0,0};
int seventh_row[] = {0,0,0,0,0};
int eighth_row[] =  {0,0,0,0,0};

enum LED_ROW_CONTROL {LED_ROW_CONTROL_start, shift_down};
int LED_ROWS[] = {row_1_pin, row_2_pin, row_3_pin, row_4_pin, row_5_pin, row_6_pin, row_7_pin, row_8_pin};
int LED_COLS[] = {col_1_pin, col_2_pin, col_3_pin, col_4_pin, col_5_pin};

Tick_LED_ROW_CONTROL(int state) {
    switch(state) {
        case LED_ROW_CONTROL_start:
            state = shift_down;
            break;
        case shift_down:
            state = shift_down;
            break;
        default:
            state = LED_ROW_CONTROL_start;
            break;
    }
    switch(state) {
        case LED_ROW_CONTROL_start:
            break;
        case shift_down:
                for (int i = 0; i < 5; i++) {
                    eighth_row[i] = seventh_row[i];
                    seventh_row[i] = sixth_row[i];
                    sixth_row[i] = fifth_row[i];
                    fifth_row[i] = fourth_row[i];
                    fourth_row[i] = third_row[i];
                    third_row[i] = second_row[i];
                    second_row[i] = first_row[i];
                }
                for (int i = 0; i < 5; i++)
                   first_row[i] = next_row_in[i];
            break;
        default:
            break;
    }
    Serial.print("shifting...\n");
    return state;
}

enum LED_MATRIX_STATES {LED_MATRIX_start, LED_ROW_1, LED_ROW_2, LED_ROW_3, LED_ROW_4, LED_ROW_5, LED_ROW_6, LED_ROW_7, LED_ROW_8};
Tick_LED_MATRIX(int state) {
    for (auto x : LED_ROWS)
      digitalWrite(x, LOW);
  
    for (auto x : LED_COLS)
      digitalWrite(x, HIGH);

    switch(state) {
        case LED_MATRIX_start:
            state = LED_ROW_1;
            break;
        case LED_ROW_1:
            state = LED_ROW_2;
            break;
        case LED_ROW_2:
            state = LED_ROW_3;
            break;
        case LED_ROW_3:
            state = LED_ROW_4;
            break;
        case LED_ROW_4:
            state = LED_ROW_5;
            break;
        case LED_ROW_5:
            state = LED_ROW_6;
            break;
        case LED_ROW_6:
            state = LED_ROW_7;
            break;
        case LED_ROW_7:
            state = LED_ROW_8;
            break;
        case LED_ROW_8:
            state = LED_ROW_1;
            break;
        default:
            state = LED_MATRIX_start;
            break;
    }
    switch(state) {
        case LED_MATRIX_start:
            break;
        case LED_ROW_1:
            for (int i = 0; i < 5; i++) {
                if (first_row[i])
                    display_on_LED_matrix(1, i);
            }
            //Serial.print("Case LED_ROW_1\n");
            break;
        case LED_ROW_2:
            for (int i = 0; i < 5; i++) {
                if (second_row[i])
                    display_on_LED_matrix(2, i);
            }
            break;
        case LED_ROW_3:
            for (int i = 0; i < 5; i++) {
                if (third_row[i])
                    display_on_LED_matrix(3, i);
            }
            break;
        case LED_ROW_4:
            for (int i = 0; i < 5; i++) {
                if (fourth_row[i])
                    display_on_LED_matrix(4, i);
            }
            break;
        case LED_ROW_5:
            for (int i = 0; i < 5; i++) {
                if (fifth_row[i])
                    display_on_LED_matrix(5, i);
            }
            break;
        case LED_ROW_6:
            for (int i = 0; i < 5; i++) {
                if (sixth_row[i])
                    display_on_LED_matrix(6, i);
            }
            break;
        case LED_ROW_7:
            for (int i = 0; i < 5; i++) {
                if (seventh_row[i])
                    display_on_LED_matrix(7, i);
            }
            break;
        case LED_ROW_8:
            for (int i = 0; i < 5; i++) {
                if (eighth_row[i])
                    display_on_LED_matrix(8, i);
            }
            break;
        default:
            break;
    }
    return state;
}

int other_output_pins[] = {buzzer_pin, row_6_pin, row_8_pin, col_2_pin, col_3_pin, row_5_pin, col_5_pin, row_7_pin, row_2_pin, col_1_pin, row_4_pin, col_4_pin, row_1_pin, row_3_pin};

void display_on_LED_matrix(int row, int col) {
    digitalWrite(LED_ROWS[row-1], HIGH);
    digitalWrite(LED_COLS[col], LOW);
}