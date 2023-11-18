void Test() {
    Serial.print("Test");
}

enum SVNSEG_STATES {start, display_three, display_two, display_one, display_zero};
int A=1, B=2, C=3, D=4, E=5, F=6, G=7;
int D1=8, D2=9, D3=10, D4=11;
int display_pins[] = {A, B, C, D, E, F, G, D1, D2, D3, D4};
Tick_SVNSEG(int state) {
    static int ones = 0;
    static int tens = 0;
    static int hundreds = 0;
    static int thousands = 0;

    char pin_to_display_on;
    int num_to_display = 0;

    switch(state) {
        case start:
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
            state = start;
            break;
    }
    switch(state) {
        case start:
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

    digitalWrite(pin_to_display_on, HIGH);
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