/*
 * display_memory.c
 *
 *  Created on: Feb 20, 2020
 *      Author: Dhruva
 */

#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "MKL25Z4.h"

#include "global_defines.h"
#include "fsl_debug_console.h"
#include "memtest.h"
#include "source/logger.h"

int j = 0;

#define BYTE_TO_BINARY_PATTERN " 0b%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte) \
	(byte & 0x80 ? '1' : '0'), \
	(byte & 0x40 ? '1' : '0'), \
	(byte & 0x20 ? '1' : '0'), \
	(byte & 0x10 ? '1' : '0'), \
	(byte & 0x08 ? '1' : '0'), \
	(byte & 0x04 ? '1' : '0'), \
	(byte & 0x02 ? '1' : '0'), \
	(byte & 0x01 ? '1' : '0')

void display_memory(uint8_t* mem, uint8_t num_bytes)
{

	if(num_bytes<=32)
	{
	uint32_t *ptr = (uint32_t*)mem;
	int8_t index = 0;
	int8_t b_index = 0;
	uint8_t iter = num_bytes / 4;
	for(index = 0; index < iter; index++)
	{

		PRINTF("0x%08X 0x%08X", ptr, *ptr);

		for(b_index = 3; b_index >= 0; b_index--){
			PRINTF(BYTE_TO_BINARY_PATTERN"\t", BYTE_TO_BINARY(*(((uint8_t *)ptr) + b_index)));
		}
		PRINTF("\r\n");
		ptr = ((uint32_t*)ptr)+1;
	}

	}
	else
	{

    printf("Error");
	}
	//
}

