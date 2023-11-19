int C5 = 523, D5 = 587, E5 = 659, F5 = 698, G5 = 784, note_A5 = 880, B5 = 988;
int C6 = 1047, D6 = 1175, E6 = 1319, F6 = 1397, G6 = 1568, note_A6 = 1760, B6 = 1976;
int C7 = 2093, D7 = 2349, E7 = 2637, F7 = 2794, G7 = 3136, note_A7 = 3520, B7 = 3951;
int C8 = 4186, D8 = 4699, E8 = 5274, F8 = 5588, G8 = 6272, note_A8 = 7040, B8 = 7902;

int tetris_buzzer_1[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    E7, E7, E7, E7, B7, B7, C7, C7, D7, D7, D7, D7, C7, C7, B7, B7,
    note_A7, note_A7, note_A7,  0, note_A7, note_A7, C7, C7, E7, E7, E7, E7, D7, D7, C7, C7,
    B7, B7, B7,  0, B7, B7, C7, C7, D7, D7, D7, D7, E7, E7, E7, E7,
    C7, C7, C7, C7, note_A7, note_A7, note_A7,  0, note_A7, note_A7, note_A7, note_A7,  0,  0,  0, 0,

     0,  0,  0, D7, D7, D7, D7, F7, F7, note_A7, note_A7, note_A7, 0,
    G7, G7, F7, F7, E7, E7, E7,  0, 0,  0, C7, C7, E7, E7, E7, E7, D7, D7, C7, C7, B7, B7, B7, B7,  0,  0, C7, C7,
    D7, D7, D7, D7, E7, E7, E7, E7, C7, C7, C7, C7, note_A7, note_A7, note_A7,  0,
    note_A7, note_A7, note_A7, note_A7
};
int tetris_buzzer_2[] = {E6, E6, E7, E7, E6, E6, E7, E7, E6, E6, E7, E7};

int tetris_rythm[] = {
    10, 10, 10, 10, 10000, 10000, 1000, 1000, 100, 100, 100, 100, 1000, 1000, 10000, 10000,
    10000, 10000, 10000,  0, 10000, 10000, 1000, 1000, 10, 10, 10, 10, 100, 100, 1000, 1000,
    10000, 10000, 10000,  0, 10000, 10000, 1000, 1000, 100, 100, 100, 100, 10, 10, 10, 10,
    1000, 1000, 1000, 1000, 10000, 10000, 10000,  0, 10000, 10000, 10000, 10000,  0,  0,  0, 0,

    0,  0,  0, 10000, 10000, 10000, 10000, 100, 100, 1, 1, 1, 0,
    10, 10, 100, 100, 1000, 1000, 1000,  0, 0,  0,
    
    1000, 1000, 10, 10, 10, 10, 100, 100, 1000, 1000, 10000, 10000, 10000, 10000,  0,  0, 
    
    1000, 1000, 100, 100, 100, 100, 10, 10, 10, 10, 1000, 1000, 1000, 1000, 10000, 10000, 10000,  0,
    10000, 10000, 10000, 10000,
    //1, 1, 1, 1,

    0,0,0,0,0,0,0,0
};