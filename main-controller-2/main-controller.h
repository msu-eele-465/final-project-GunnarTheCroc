void init_ports() {
    // inputs
    // button
    P1DIR &= ~BIT2; 
    P1REN |= BIT2;  
    P1OUT |= BIT2;  

    // switch
    P1DIR &= ~BIT3; 
    P1REN |= BIT3;  
    P1OUT |= BIT3;  

    // servo PWM
    P1DIR |= BIT4;

    // buzzer
    P1DIR |= BIT5;

    // display on/off
    P1DIR |= BIT6;

    // display jp/en
    P1DIR |= BIT7;
}
