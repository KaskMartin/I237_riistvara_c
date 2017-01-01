#include <avr/pgmspace.h>
#include "hmi_msg.h"

static const char s1[] PROGMEM = "January";
static const char s2[] PROGMEM = "February";
static const char s3[] PROGMEM = "March";
static const char s4[] PROGMEM = "April";
static const char s5[] PROGMEM = "May";
static const char s6[] PROGMEM = "June";

PGM_P const nameMonth[] PROGMEM = {s1, s2, s3, s4, s5, s6};

const char help_cmd[] PROGMEM = CLI_HELP_CDM_MSG;
const char help_help[] PROGMEM = CLI_HELP_HELP_MSG;
const char ver_cmd[] PROGMEM = CLI_VER_CMD_MSG;
const char ver_help[] PROGMEM = CLI_VER_HELP_MSG;
const char ascii_cmd[] PROGMEM = CLI_ASCII_CMD_MSG;
const char ascii_help[] PROGMEM = CLI_ASCII_HELP_MSG;
const char month_cmd[] PROGMEM = CLI_MONTH_CMD_MSG;
const char month_help[] PROGMEM = CLI_MONTH_HELP_MSG;