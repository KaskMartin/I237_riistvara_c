#include <avr/pgmspace.h>
#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define VER_FW "Version: %S built on: %S %S\n"
#define VER_LIBC "avr-libc version: %S\n"
#define MONTH_PROMPT "Enter Month name first letter >"  
#define STUD_NAME "Martin Kask"

const char s1[] PROGMEM = "January";
const char s2[] PROGMEM = "February";
const char s3[] PROGMEM = "March";
const char s4[] PROGMEM = "April";
const char s5[] PROGMEM = "May";
const char s6[] PROGMEM = "June";

PGM_P const nameMonth[] PROGMEM = {s1,s2,s3,s4,s5,s6};
#endif /* _HMI_MSG_H_ */