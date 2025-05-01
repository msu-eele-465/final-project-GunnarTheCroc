#include <msp430fr2355.h>
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

    while (true) {

		// idle state
		while(state == 0) {
			buzzer_off();
			screen_off();
			poll_button();
			if (button == 0) {
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
			buzzer_off();
			poll_switch();
			if (swtch == 0) {
				lang_jp();
			} else {
				lang_en();
			}
			screen_on();
			poll_button();
			if (button == 0) {
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
