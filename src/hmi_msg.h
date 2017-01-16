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
#include <avr/pgmspace.h>

#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define VER_FW "Version: %S built on: %S %S\n"
#define VER_LIBC "avr-libc version: %S "
#define VER_GCC "avr-gcc version: %S\n"  
#define STUD_NAME "Martin Kask"
#define UPTIME "Uptime: %lu s"

#define CLI_PRINT_HELP_MSG "Implemented commands:\n"
#define CLI_PRINT_CMD_ERROR_MSG "Command not implemented.\n Use <help> to get help.\n"
#define CLI_PRINT_CMD_ARG_ERROR_MSG "To few or too many arguments for this command\nUse <help>\n"
#define CLI_HELP_CDM_MSG "help"
#define CLI_HELP_HELP_MSG "Get help"
#define CLI_VER_CMD_MSG "version"
#define CLI_VER_HELP_MSG "Print FW version"
#define CLI_ASCII_CMD_MSG "ascii"
#define CLI_ASCII_HELP_MSG "print ASCII tables"
#define CLI_MONTH_CMD_MSG "month"
#define CLI_MONTH_HELP_MSG "Find matching month from lookup list. Usage: month <string>"
#define OUT_OF_MEMORY_MSG "System memory is too low. Please remove unused cards."
#define UNABLE_TO_DETECT_CARD_MSG "Unable to detect card."
#define CARD_ALRAEDY_REGISTERED_MSG1 "Card with code: "
#define CARD_ALRAEDY_REGISTERED_MSG2 ". already in database."

#define CARD_SELECTED_MSG "Card selected"
#define UID_SIZE_MSG "UID size: 0x%02X"
#define UID_SAK_MSG "UID sak: 0x%02X"
#define CARD_UID_MSG "Card UID: "
#define CARD_NOT_SELECTED_MSG "Unable to select card.\n"
#define READ_CMD "read"
#define READ_HELP "Read and print out card info for the card currently near the reader"
#define ADD_CMD "add"
#define ADD_HELP "Add a new rfid card to memory. Usage: add <username>"
#define LIST_CMD "list"
#define LIST_HELP "List cards saved to system"
#define NO_CARDS_ADDED_MSG "No cards added"

extern PGM_P const nameMonth[];

extern const char help_cmd[];
extern const char help_help[];
extern const char ver_cmd[];
extern const char ver_help[];
extern const char ascii_cmd[];
extern const char ascii_help[];
extern const char month_cmd[];
extern const char month_help[];

extern const char read_cmd[];
extern const char read_help[];
extern const char add_cmd[];
extern const char add_help[];
extern const char list_cmd[];
extern const char list_help[];
#endif /* _HMI_MSG_H_ */