/*  Unlocker9000+
    Unlocker9000+ is RFID door access controller for Arduino Mega 2560 chip.

    Copyright (C) 2016  Martin Kask
    Contact: kask.martin@gmail.com

    This file is part of Unlocker9000+.

    Unlocker9000+ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Unlocker9000+ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "../lib/hd44780_111/hd44780.h"
#include "../lib/andygock_avr-uart/uart.h"
#include "hmi_msg.h"
#include "print_helper.h"
#include "cli_microrl.h"

typedef struct cli_cmd {
    PGM_P cmd;
    PGM_P help;
    void (*func_p)();
    const uint8_t func_argc;
}
cli_cmd_t;

const cli_cmd_t cli_cmds[] = {
    {help_cmd, help_help, cli_print_help, 0},
    {ver_cmd, ver_help, cli_print_ver, 0},
    {ascii_cmd, ascii_help, cli_print_ascii_tbls, 0},
    {month_cmd, month_help, cli_handle_month, 1}
};

void cli_print(const char *str)
{
    printf("%s", str);
}

char cli_get_char(void)
{
    if (uart0_peek() != UART_NO_DATA) {
        return uart0_getc() & UART_STATUS_MASK;
    } else {
        return 0x00;
    }
}

void cli_print_help(const char *const *argv)
{
    (void) argv;
    printf_P(PSTR("\n"));
    printf_P(PSTR(CLI_PRINT_HELP_MSG));
    for (uint8_t i = 0; i < NUM_ELEMS(cli_cmds); i++) {
        printf_P(cli_cmds[i].cmd);
        printf_P(PSTR(" : "));
        printf_P(cli_cmds[i].help);
        printf_P(PSTR("\n"));
    }
}

void print_verinf(FILE *stream)
{
    fprintf_P(stream, PSTR(VER_FW),
              PSTR(GIT_DESCR), PSTR(__DATE__), PSTR(__TIME__));
    fprintf_P(stream, PSTR(VER_LIBC), PSTR(__AVR_LIBC_VERSION_STRING__));
    fprintf_P(stream, PSTR(VER_GCC), PSTR(__VERSION__));
}
void cli_print_ver(const char *const *argv)
{
    (void) argv;
    printf_P(PSTR("\n"));
    print_verinf(stdout);
}

void cli_print_ascii_tbls(const char *const *argv)
{
    (void) argv;
    printf_P(PSTR("\n"));
    /* Print ASCII Table */
    print_ascii_tbl(stdout);
    unsigned char ascii[128] = {0};
    for (unsigned char i = 0; i < 128; i++) {
        ascii[i] = i;
    }
    print_for_human(stdout, ascii, 128);
}

void cli_handle_month(const char *const *argv)
{
    printf_P(PSTR("\n"));
    /*Start printing Months to LCD on second line */
    lcd_goto(0x40);
    char lcd_length_left = 16;
    /*Loop to find and print Month names to stdout and LCD*/
    for (int i = 0; i < 6; i++) {
        if (!strncmp_P(argv[1], (PGM_P)pgm_read_word(&nameMonth[i]), strlen(argv[1]))) {
            char lcd_already_used;
            lcd_already_used = fprintf_P(stdout, (PGM_P)pgm_read_word(&nameMonth[i]));
            printf_P(PSTR("\n"));
            lcd_puts_P((PGM_P)pgm_read_word(&nameMonth[i]));
            lcd_putc(' ');
            lcd_length_left -= (lcd_already_used + 1);
        }
    }
    for (; lcd_length_left >= 0; lcd_length_left--) {
        lcd_putc(' ');
    }
}

void cli_print_cmd_error(void)
{
    printf_P(PSTR("\n"));
    printf_P(PSTR(CLI_PRINT_CMD_ERROR_MSG));
}

void cli_print_cmd_arg_error(void)
{
    printf_P(PSTR("\n"));
    printf_P(PSTR(CLI_PRINT_CMD_ARG_ERROR_MSG));
}

int cli_execute(int argc, const char *const *argv)
{
    for (uint8_t i = 0; i < NUM_ELEMS(cli_cmds); i++) {
        if (!strcmp_P(argv[0], cli_cmds[i].cmd)) {
            // Test do we have correct arguments to run command
            // Function arguments count shall be defined in struct
            if ((argc - 1) != cli_cmds[i].func_argc) {
                cli_print_cmd_arg_error();
                return 0;
            }
            // Hand argv over to function pointer,
            // cross fingers and hope that funcion handles it properly
            cli_cmds[i].func_p(argv);
            return 0;
        }
    }
    cli_print_cmd_error();
    return 0;
}