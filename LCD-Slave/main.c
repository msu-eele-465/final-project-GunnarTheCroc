#include <stdint.h>
#include <stdbool.h>
#include "lcd.h"
#include "intrinsics.h"

int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    define_ports();

    // Disable low-power mode / GPIO high-impedance
    PM5CTL0 &= ~LOCKLPM5;

    int screen;
    int english;

    while (true) {

        start_up();

        while (true) {

            screen = P1IN;
            screen &= BIT2;
            english = P1IN;
            english &= BIT3;

            if (screen != 0) {
                if (english == 0) {
                    eng_text();
                } else {
                    jp_text();
                }
            } else {
                clear_display();
            }
            __delay_cycles(50000);
        }
    }
}
