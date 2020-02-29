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

// inspired by https://www.geeksforgeeks.org/count-total-bits-number/
int32_t count_bits(uint32_t n) {
	uint32_t counter = 0;
	while(n){
		counter++;
		n >>= 1;
	}
	return counter;
}

// inspired by https://www.geeksforgeeks.org/invert-actual-bits-number/
void invert_block(uint8_t* mem, uint8_t offset, uint8_t num_bytes){
	if(num_bytes <= 32){
		uint32_t num_bits;
		uint8_t* inv = (uint8_t*)calloc(num_bytes, sizeof(uint8_t));
		if(inv == NULL){
			inv_b = MEM_FAILED;
			Log_string("Write memory: split array failed to allocate");
		}
		uint8_t offset1 = offset; // save offset to local var
		// store values (numbytes = num of indexes) to intermediate array
		for(int i = 0; i < num_bytes; i++){
			inv[i] = mem[offset1];
			offset1++;
		}
		// invert bits over number of number of bytes (i.e. each index in mem array)
		for(int j = 0; j < num_bytes; j++){
			num_bits = count_bits((uint32_t)inv[j]);
			for(int k = 0; k < num_bits; k++){
				inv[j] = (inv[j] ^ (1 << k));
			}
		}
		// feed inverted values back to mem array
		for(int l = 0; l < num_bytes; l++){
			mem[offset] = inv[l];
			offset++;
		}
		// free intermediate array memory
		free(inv);
		inv_b = MEM_SUCCESS;
	} else{
		inv_b = MEM_FAILED;
	}
	if(inv_b == MEM_SUCCESS){
		LED_flash(GREEN);
	} else{
		LED_flash(RED);
	}
}
