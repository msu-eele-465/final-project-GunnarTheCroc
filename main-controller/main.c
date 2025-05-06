#include <msp430.h>
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

	// setup IRQ
	P3IFG &= ~BIT0;
	P3IE |= BIT0;
	__enable_interrupt();

    while (true) {

		// idle state
		while(state == 0) {
			buzzer_off();
			screen_off();
			if (train_action == true) {
				state = 1;
			}
		}

		// arrival state
		while(state == 1) {
			buzzer_on();
			screen_off();
			if (counter == 0) {
				state = 2;
			}
		}

		// english-japanese state
		while(state == 2) {
			train_action = false;
			buzzer_off();
			if (english) {
				lang_en();
			} else {
				lang_jp();
			}
			screen_on();
			if (train_action == true) {
				state = 3;
			}
		}

		// departing state
		while(state == 3) {
			buzzer_on();
			screen_off();
			if (counter == 0) {
				state = 0;
			}
		}
    }
}

//-------------------Interrupt Service Routines
#pragma vector = PORT3_VECTOR
__interrupt void ISR_Port3_S1(void) {
	train_action = true;
	P3IFG &= ~BIT0;
}
