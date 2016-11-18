#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main (void)
{
    /* set pin 25 high (led on)*/
    DDRA |= _BV(DDA3);

    while (1) {
        /* set pin 25 high (led on)*/
        PORTA |= _BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
        /* set pin 25 low (led off) */
        PORTA &= ~_BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
    }
}