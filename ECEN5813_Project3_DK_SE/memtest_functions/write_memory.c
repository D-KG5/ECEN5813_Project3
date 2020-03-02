/*
 * write_memory.c
 *
 *  Created on: Feb 20, 2020
 *      Author: Dhruva
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "board.h"
#include "MKL25Z4.h"

#include "global_defines.h"
#include "memtest.h"
#include "source/logger.h"

mem_status_t mem_wr;

void write_memory(uint8_t* mem, uint8_t offset, uint8_t len, uint16_t val){
	uint8_t* split = (uint8_t*)calloc(len, sizeof(uint8_t));
	if(split == NULL){
		mem_wr = MEM_FAILED;
		Log_string("Write memory: split array failed to allocate");
	}else{
		// split value to fit uint8_t blocks
		for(int i = len - 1; i >= 0; i--){
			split[i] = val & 0x00FF;
			val = (val >> 8);
		}
		// put it back in
		for(int j = 0; j < len; j++){
			mem[offset] = split[j];
			offset++;
		}
		free(split);
		mem_wr = MEM_SUCCESS;
	}
	if(mem_wr == MEM_SUCCESS){
		LED_flash(GREEN);
	} else{
		LED_flash(RED);
	}
}
