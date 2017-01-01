#include <avr/pgmspace.h>

#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define VER_FW "Version: %S built on: %S %S\n"
#define VER_LIBC "avr-libc version: %S "
#define VER_GCC "avr-gcc version: %S\n"
#define MONTH_PROMPT "Enter Month name first letter >"  
#define STUD_NAME "Martin Kask"
#define UPTIME "Uptime: %lu s"


extern PGM_P const nameMonth[];

#endif /* _HMI_MSG_H_ */