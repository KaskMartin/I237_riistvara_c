#include <avr/pgmspace.h>
#include "hmi_msg.h"

static const char s1[] PROGMEM = "January";
static const char s2[] PROGMEM = "February";
static const char s3[] PROGMEM = "March";
static const char s4[] PROGMEM = "April";
static const char s5[] PROGMEM = "May";
static const char s6[] PROGMEM = "June";

PGM_P const nameMonth[] PROGMEM = {s1, s2, s3, s4, s5, s6};

const char help_cmd[] PROGMEM = "help";
const char help_help[] PROGMEM = "Get help";
const char ver_cmd[] PROGMEM = "version";
const char ver_help[] PROGMEM = "Print FW version";
const char ascii_cmd[] PROGMEM = "ascii";
const char ascii_help[] PROGMEM = "print ASCII tables";
const char month_cmd[] PROGMEM = "month";
const char month_help[] PROGMEM =
    "Find matching month from lookup list. Usage: month <string>";