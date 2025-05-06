#include <msp430fr2310.h>

void define_ports(void) {
    // data nibble DB7-BD4 (P1.0-1.1, P2.6-2.7)
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    P1DIR |= BIT1;
    P1OUT &= ~BIT1;
    P2DIR |= BIT6;
    P2OUT &= ~BIT6;
    P2DIR |= BIT7;
    P2OUT &= ~BIT7;

    // RS (P1.5)
    P1DIR |= BIT5;
    P1OUT &= ~BIT5;
    
    // RW (P1.6)
    P1DIR |= BIT6;
    P1OUT &= ~BIT6;

    // Enable (P1.7)
    P1DIR |= BIT7;
    P1OUT &= ~BIT7;

    // logic inputs
    // screen on/off (P1.2)
    P1DIR &= ~BIT2;
    P1REN |= BIT2;
    P1OUT |= BIT2;

    // language select (P1.3)
    P1DIR &= ~BIT3;
    P1REN |= BIT3;
    P1OUT |= BIT3;
}

// turns power on
void power_on(void) {
    P1OUT |= BIT4;
}

// turns power off
void power_off(void) {
    P1OUT &= ~BIT4;
}

// turns enable on
void enable_high(void) {
    P1OUT |= BIT7;
}

// turns enable off
void enable_low(void) {
    P1OUT &= ~BIT7;
}

void enable_pulse() {
    enable_high();
    __delay_cycles(50000);
    enable_low();
}

void rs_high(void) {
    P1OUT |= BIT5;
}

void rs_low(void) {
    P1OUT &= ~BIT5;
}

void rw_high(void) {
    P1OUT |= BIT6;
}

void rw_low(void) {
    P1OUT &= ~BIT6;
}

void set_nibble(int nibbleInt) {
    int nib0 = nibbleInt;
    if ((nib0 &= BIT0) != 0) {
        P1OUT |= BIT0;
    } else {
        P1OUT &= ~BIT0;
    }
    
    int nib1 = nibbleInt;
    if ((nib1 &= BIT1) != 0) {
        P1OUT |= BIT1;
    } else {
        P1OUT &= ~BIT1;
    }
    
    int nib2 = nibbleInt;
    if ((nib2 &= BIT2) != 0) {
        P2OUT |= BIT6;
    } else {
        P2OUT &= ~BIT6;
    }
    
    int nib3 = nibbleInt;
    if ((nib3 &= BIT3) != 0) {
        P2OUT |= BIT7;
    } else {
        P2OUT &= ~BIT7;
    }
}

void start_up() {
    power_on();
    __delay_cycles(100000);
    // set to 4 bit mode
    set_nibble(0b0010);
    enable_pulse();
    __delay_cycles(100000);
    set_nibble(0b0010);
    enable_pulse();
    __delay_cycles(100000);

    // 2 line mode, display on
    set_nibble(0b1100);
    enable_pulse();
    __delay_cycles(100000);

    // display on, cursor on, blink on
    set_nibble(0b0000);
    enable_pulse();
    __delay_cycles(100000);
    set_nibble(0b1100);
    enable_pulse();
    __delay_cycles(100000);

    // clear display
    set_nibble(0b0000);
    enable_pulse();
    __delay_cycles(100000);
    set_nibble(0b0001);
    enable_pulse();
    __delay_cycles(100000);

    // entry mode set, increment mode, shift off
    set_nibble(0b0000);
    enable_pulse();
    __delay_cycles(100000);
    set_nibble(0b0110);
    enable_pulse();
    __delay_cycles(100000);
}

void clear_display() {
    set_nibble(0b0000);
    enable_pulse();
    __delay_cycles(5000);
    set_nibble(0b0001);
    enable_pulse();
    __delay_cycles(5000);
}

void set_cursor_location(int upperNibble, int lowerNibble) {
    // expecting full address given to be 1 concatenated with 7 bit address, split into 2 nibbles
    // e.g. for first char in first line, upperNibble = 1000, lowerNibble = 0000
    set_nibble(upperNibble);
    enable_pulse();
    __delay_cycles(5000);
    set_nibble(lowerNibble);
    enable_pulse();
    __delay_cycles(5000);
}

void write_character(int upperNibble, int lowerNibble) {
    // expecting full address split into 2 nibbles
    // e.g. for 0, upperNibble = 0011, lowerNibble = 0000
    rs_high();
    set_nibble(upperNibble);
    enable_pulse();
    __delay_cycles(5000);
    set_nibble(lowerNibble);
    enable_pulse();
    __delay_cycles(5000);
    rs_low();
}

void write_by_ascii(char ch) {
    int ascii_ch = ch;
    int ascii_ch_upper = ch >> 4;
    write_character(ascii_ch_upper, ascii_ch);
}

void location_by_coords(int row, int column) {
    int upper = 0b1000;
    int lower = column - 1;
    if (row == 1) {
        upper = 0b1000;
    } else if (row == 2) {
        upper = 0b1100;
    } else {
        upper = 0b1000;
    }
    set_cursor_location(upper, lower);
} 

void write_word(char *word) {
    int i;
    for (i = 0; word[i] != '\0'; i++) {
        write_by_ascii(word[i]);
    }
}

void eng_text() {
    location_by_coords(1, 1);
    write_word("Ginza Line");
    location_by_coords(2, 1);
    write_word("Southbound");
}

void jp_text() {
    location_by_coords(1, 1);
    write_character(0b1011, 0b0111); // ki
    write_character(0b1101, 0b1110); // tenten
    write_character(0b1101, 0b1101); // n
    write_character(0b1011, 0b1011); // sa
    write_character(0b1101, 0b1110); // tenten
    write_by_ascii(32);              // space
    write_character(0b1101, 0b0111); // ra
    write_character(0b1011, 0b0010); // i
    write_character(0b1101, 0b1101); // n
    write_by_ascii(32);              // space
    location_by_coords(2, 1);
    write_character(0b1101, 0b0000); // mi
    write_character(0b1100, 0b0101); // na
    write_character(0b1101, 0b0000); // mi
    write_by_ascii(32);              // space
    write_character(0b1100, 0b1110); // ho
    write_character(0b1011, 0b0011); // u
    write_character(0b1101, 0b0010); // me
    write_character(0b1101, 0b1101); // n
    write_by_ascii(32);              // space
    write_by_ascii(32);              // space
}

