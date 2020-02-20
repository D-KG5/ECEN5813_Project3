/*
 * logger.h
 *
 *  Created on: Feb 20, 2020
 *      Author: Dhruva
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdint.h>
#include <stdbool.h>

void Log_enable(void); // begin printing log messages when called
void Log_disable(void); // ignore any log messages until re-enabled
bool Log_status(void); // returns a flag to indicate whether the logger is enabled or disabled
void Log_data(uint8_t * seq, uint8_t len); // display in hexadecimal an address and contents of a memory location, arguments are a pointer to a sequence of bytes and a specified length
void Log_string(char * string); // display a string
void Log_integer(uint8_t integer); // display an integer

// The previous three commands should include a new line after each display

#endif /* LOGGER_H_ */
