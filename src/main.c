#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

#include "uart-wrapper.h"
#include "print_helper.h"
#include "hmi_msg.h"
#include "cli_microrl.h"

#include "../lib/hd44780_111/hd44780.h"
#include "../lib/andygock_avr-uart/uart.h"
#include "../lib//helius_microrl/microrl.h"

#define __ASSERT_USE_STDERR
#define BAUD 9600
#define BLINK_DELAY_MS 100

volatile uint32_t second_counter;

// create microrl object and pointer on it
microrl_t rl;
microrl_t * prl = &rl;

static inline void init_system_clock(void)
{
    // Clear control register A
    TCCR5A = 0;
    // Clear control register B
    TCCR5B = 0;
    // CTC and fCPU/256
    TCCR5B |= _BV(WGM52) | _BV(CS52);
    // 1 s
    OCR5A = 62549;
    // Output Compare A Match Interrupt Enable
    TIMSK5 |= _BV(OCIE5A);
}

static inline void prog_init()
{
    //Start system clock
    init_system_clock();
    // Set pin 3 of PORTA for output
    DDRA |= _BV(DDA3);
    // Initialize and define UARTs
    uart0_init(UART_BAUD_SELECT(BAUD, F_CPU));
    uart3_init(UART_BAUD_SELECT(BAUD, F_CPU));
    stdin = stdout = &uart0_io;
    stderr = &uart3_out;
    //Enable the use of interupts
    sei();
    //Enable lcd and clear the screen
    lcd_init();
    lcd_clrscr();
}

static inline void print_start_inf()
{
    print_verinf(stderr);
    /*Print my name to stdout and LCD*/
    fprintf_P(stdout, PSTR(STUD_NAME "\n"));
    lcd_puts_P(PSTR(STUD_NAME));
}

static inline void heartbeat ()
{
    static uint32_t time_prev;
    uint32_t time_cpy;
    time_cpy = second_counter;

    if (time_cpy != time_prev) {
        /* Toggle LED in Arduino Mega pin 25 */
        PORTA ^= _BV(PORTA3);
        fprintf_P(stderr, PSTR(UPTIME "\n"), time_cpy);
        time_prev = time_cpy;
    }
}

static inline void microrl_initalize ()
{
    // call init with ptr to microrl instance and print callback
    microrl_init (prl, cli_print);
    // set callback for execute
    microrl_set_execute_callback (prl, cli_execute);
}

void main (void)
{
    prog_init();
    print_start_inf();
    microrl_initalize();

    while (1) {
        heartbeat();
        //Get input from user via commandline and execute the commands
        char ch = cli_get_char();
        microrl_insert_char (prl, ch);
    }
}

/* System clock ISR */
ISR(TIMER5_COMPA_vect)
{
    second_counter++;
}