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

mem_status_t dis_m;

// inspired by https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
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

void display_memory(uint8_t* mem, uint8_t num_bytes){
	if(num_bytes <= MAX_SIZE){
		uint32_t *bin_ptr = (uint32_t*)mem;
		uint8_t iter = num_bytes / 4;
		for(int8_t index = 0; index < iter; index++){
			PRINTF("0x%08X 0x%08X", bin_ptr, *bin_ptr);
			for(int8_t b_index = 3; b_index >= 0; b_index--){
				PRINTF(BYTE_TO_BINARY_PATTERN"\t", BYTE_TO_BINARY(*(((uint8_t *)bin_ptr) + b_index)));
			}
			PRINTF("\r\n");
			bin_ptr = ((uint32_t*)bin_ptr) + 1;
		}
		dis_m = MEM_SUCCESS;
//		Log_data(mem, num_bytes);
	} else{
		Log_string("Out of range");
		dis_m = MEM_FAILED;
	}

	if(dis_m == MEM_SUCCESS){
		LED_flash(GREEN);
	} else{
		LED_flash(RED);
	}
}

