#include <msp430fr2310.h>
#include <stdint.h>
#include <stdbool.h>
#include "intrinsics.h"
#include "main-controller.h"

int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

	init_ports();

    // Disable low-power mode / GPIO high-impedance
    PM5CTL0 &= ~LOCKLPM5;

	int button;
	int swtch;
	int state = 0;

    while (true) {
		button = P1IN;
		button &= BIT2;
		
		swtch = P1IN;
		swtch &= BIT3;

		while(state == 0) {
			P1OUT |= BIT4;
			P1OUT |= BIT5;
			P1OUT |= BIT6;
			P1OUT |= BIT7;

			__delay_cycles(10000);
		
			P1OUT &= ~ BIT4;
			P1OUT &= ~ BIT5;
			P1OUT &= ~ BIT6;
			P1OUT &= ~ BIT7;
		}
    }
}
