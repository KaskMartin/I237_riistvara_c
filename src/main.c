#include <stdio.h>
#include <string.h>
#define __ASSERT_USE_STDERR
#include <assert.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart-wrapper.h"
#include "print_helper.h"
#include "hmi_msg.h"
#include <avr/pgmspace.h>
#include "../lib/hd44780_111/hd44780.h"
#include "../lib/andygock_avr-uart/uart.h"
#include <avr/interrupt.h>

#define BAUD 9600
#define BLINK_DELAY_MS 100

volatile uint32_t second_counter;

static inline void init_system_clock(void)
{
    TCCR5A = 0; // Clear control register A
    TCCR5B = 0; // Clear control register B
    TCCR5B |= _BV(WGM52) | _BV(CS52); // CTC and fCPU/256
    OCR5A = 62549; // 1 s
    TIMSK5 |= _BV(OCIE5A); // Output Compare A Match Interrupt Enable
}

static inline void prog_init()
{
    //Start system clock
    init_system_clock();
    /* Set pin 3 of PORTA for output */
    DDRA |= _BV(DDA3);
    /* Init error console as stderr in UART3 and print user code info */
    uart0_init(UART_BAUD_SELECT(BAUD, F_CPU));
    uart3_init(UART_BAUD_SELECT(BAUD, F_CPU));
    //Enable the use of interupts
    sei();
    stdin = stdout = &uart0_io;
    stderr = &uart3_out;
    //Enable lcd and clear the screen
    lcd_init();
    lcd_clrscr();
}

static inline void print_verinf()
{
    fprintf_P(stderr, PSTR(VER_FW),
              PSTR(GIT_DESCR), PSTR(__DATE__), PSTR(__TIME__));
    fprintf_P(stderr, PSTR(VER_LIBC), PSTR(__AVR_LIBC_VERSION_STRING__));
    fprintf_P(stderr, PSTR(VER_GCC), PSTR(__VERSION__));
}

static inline void print_start_inf()
{
    print_verinf();
    /*Print my name to stdout and LCD*/
    fprintf_P(stdout, PSTR(STUD_NAME "\n"));
    lcd_puts_P(PSTR(STUD_NAME));
    /* Print ASCII Table */
    print_ascii_tbl(stdout);
    unsigned char ascii[128] = {0};

    for (unsigned char i = 0; i < 128; i++) {
        ascii[i] = i;
    }

    print_for_human(stdout, ascii, 128);
    fprintf_P(stdout, PSTR(MONTH_PROMPT));
}

static inline void month_lookup()
{
    /*Compare and output calendar names*/
    char inBuf = ' ';
    fscanf(stdin, "%c", &inBuf);
    fprintf(stdout, "%c\n", inBuf);
    /*Start printing Months to LCD on second line */
    lcd_goto(0x40);

    /*Loop to find and print Month names to stdout and LCD*/
    for (int i = 0; i < 6; i++) {
        if (!strncmp_P(&inBuf, (PGM_P)pgm_read_word(&nameMonth[i]), 1)) {
            fprintf_P(stdout, PSTR("%S\n"), (PGM_P)pgm_read_word(&nameMonth[i]));
            lcd_puts_P((PGM_P)pgm_read_word(&nameMonth[i]));
            lcd_putc(' ');
        }
    }

    fprintf_P(stdout, PSTR(MONTH_PROMPT));

    for (int i = 1; i <= 16; i++) {
        lcd_putc(' ');
    }
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

void main (void)
{
    prog_init();
    print_start_inf();

    while (1) {
        heartbeat();

        if (uart0_available()) {
            month_lookup();
        }
    }
}

/* System clock ISR */
ISR(TIMER5_COMPA_vect)
{
    second_counter++;
}