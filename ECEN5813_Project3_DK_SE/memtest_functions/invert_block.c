/*
 * invert_block.c
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
#include "fsl_debug_console.h"
#include "memtest.h"
#include "source/logger.h"

mem_status_t inv_b;

// inspired by https://www.geeksforgeeks.org/invert-actual-bits-number/
void invert_block(uint8_t* mem, uint8_t offset, uint8_t num_bytes){
	// check if out of range
	if(offset <= MAX_SIZE){
		// set an intermediate pointer to access the mem alloc
		uint8_t * inv = (uint8_t*)(mem + offset);
		if(inv == NULL){
			inv_b = MEM_FAILED;
			Log_string("Write memory: inv array failed to allocate");
		}else{
			// xor bytes to invert and feed it back in
			for(int i = 0; i < num_bytes; i++){
				inv[i] = inv[i] ^ 0xFF;
			}
			inv_b = MEM_SUCCESS;
//			Log_data(mem, 32);
		}
	} else{
		inv_b = MEM_FAILED;
		Log_string("Out of Range");
	}
	if(inv_b == MEM_SUCCESS){
		LED_flash(GREEN);
	} else{
		LED_flash(RED);
	}
}
