#include <avr/pgmspace.h>

#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define VER_FW "Version: %S built on: %S %S\n"
#define VER_LIBC "avr-libc version: %S "
#define VER_GCC "avr-gcc version: %S\n"
#define MONTH_PROMPT "Enter Month name first letter >"  
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

extern PGM_P const nameMonth[];

extern const char help_cmd[];
extern const char help_help[];
extern const char ver_cmd[];
extern const char ver_help[];
extern const char ascii_cmd[];
extern const char ascii_help[];
extern const char month_cmd[];
extern const char month_help[];

#endif /* _HMI_MSG_H_ */