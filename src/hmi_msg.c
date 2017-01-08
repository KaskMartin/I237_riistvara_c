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