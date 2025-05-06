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

    while (true) {

        start_up();
        start_up();


        while (true) {
            clear_display();
            write_word("Ginza Line");
        }
    }
}
