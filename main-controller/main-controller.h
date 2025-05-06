#include <msp430.h>

bool english = false;
int language = 0;
bool train_action = false;
int counter = 0;
int state = 0;

void init_ports() {
    // inputs
    // button
    P3DIR &= ~BIT0; 
    P3REN |= BIT0;  
    P3OUT |= BIT0;  
    P3IES |= BIT0;

    // switch
    P3DIR &= ~BIT1; 
    P3REN |= BIT1;  
    P3OUT |= BIT1; 

    // servo PWM
    P5DIR |= BIT0;
	P5OUT &= ~BIT0;

    // buzzer
    P5DIR |= BIT1;
    P5OUT &= ~BIT1;

    // display on/off
    P5DIR |= BIT2;
    P5OUT &= ~BIT2;
    
    // display jp/en
    P5DIR |= BIT3;
    P5OUT &= ~BIT3;
    
}

void poll_switch() {
    language = P3IN;
    language &= BIT1;
}

void buzzer_on() {
    P5OUT |= BIT1;
}

void buzzer_off() {
    P5OUT &= ~BIT1;
}

void screen_on() {
    P5OUT |= BIT2;
}

void screen_off() {
    P5OUT &= ~BIT2;
}

void lang_jp() {
    P5OUT |= BIT3;
}

void lang_en() {
    P5OUT &= ~BIT3;
}

