#include "msp430fr2355.h"
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

void pwm_timer_setup() {
    // setup Timer B0
    TB0CTL |= TBCLR;        
    TB0CTL |= TBSSEL__ACLK; 
    TB0CTL |= MC__UP;       

    // setup compare registers
    TB0CCR0 = 655;
    TB0CCR1 = 49;

    TB0CCTL0 &= ~CCIFG;
    TB0CCTL0 |= CCIE;
    
    TB0CCTL1 &= ~CCIFG;
    TB0CCTL1 |= CCIE;
}

void servo_closed() {
    TB0CCR1 = 82;
}

void servo_open() {
    TB0CCR1 = 49;
}

void pwm_high() {
    P5OUT |= BIT0;
}

void pwm_low() {
    P5OUT &= ~BIT0;
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

