int count = 1234;

void Test() {
        Serial.print("\nTest");
}

enum SVNSEG_STATES {SVNSEG_start, display_three, display_two, display_one, display_zero};
int A=29, B=30, C=27, D=24, E=25, F=28, G=26;
int D1=34, D2=35, D3=33, D4=32;

int display_pins[] = {A, B, C, D, E, F, G, D4, D3, D2, D1};
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
            tone(buzzer_pin, 783);
            break;
        case buzz_off:
            noTone(buzzer_pin);
            break;
        default:
            break;
    }
    return state;
}

int other_output_pins[] = {buzzer_pin};
