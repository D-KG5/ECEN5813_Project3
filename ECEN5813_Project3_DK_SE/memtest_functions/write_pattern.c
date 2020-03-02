/*
 * write_pattern.c
 *
 *  Created on: Feb 20, 2020
 *      Author: Dhruva
 */

#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "MKL25Z4.h"

#include "memtest.h"
#include "global_defines.h"
#include "source/logger.h"
#include<stdlib.h>
mem_status_t pattern_wr;

uint16_t m=550;
uint8_t a=3;
uint8_t c=5;

uint8_t * gen_pattern(uint8_t num_bytes, uint8_t seed){
	uint8_t* ptr;
	if(num_bytes > MAX_SIZE){
		pattern_wr = MEM_FAILED;
	}else{
		ptr = (uint8_t*)malloc(num_bytes*sizeof(uint8_t));
		for(int i=0;i<num_bytes;i++){
			ptr[i]=seed;
			seed= (a*seed+c)%(m);
		}
		pattern_wr = MEM_SUCCESS;
	}
	return ptr;
}

void write_pattern(uint8_t *mem, uint8_t num_bytes, uint8_t seed){
	uint8_t* trt;
	if(num_bytes > MAX_SIZE){
		pattern_wr = MEM_FAILED;
	}else{
		trt = (uint8_t*)malloc(num_bytes*sizeof(uint8_t));
		trt = gen_pattern(num_bytes,seed);

		for(int i = 0; i < num_bytes; ++i){
			*mem = trt[i];
			mem++;
		}
		pattern_wr = MEM_SUCCESS;
	}
	if(pattern_wr == MEM_SUCCESS){
		LED_flash(GREEN);
	} else{
		LED_flash(RED);
	}
}
