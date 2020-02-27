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
#include "source/logger.h"
#include<stdlib.h>
mem_status_t pattern_wr;

uint16_t m=550;
uint8_t a=3;
uint8_t c=5;

uint8_t * gen_pattern(uint8_t num_bytes, uint8_t seed){
	uint8_t* ptr;
	if(num_bytes>32)
		{
			printf("Error");
		}
		else
		{

	ptr = (uint8_t*)malloc(num_bytes*sizeof(uint8_t));
	for(int i=0;i<num_bytes;i++)
	{
		ptr[i]=seed;
		seed= (a*seed+c)%(m);
	}
		}

	return ptr;
}

void write_pattern(uint8_t *mem, uint8_t num_bytes, uint8_t seed){
	uint8_t* trt;
	trt = (uint8_t*)malloc(num_bytes*sizeof(uint8_t));
	trt=gen_pattern(num_bytes,seed);
	// testing
	//uint8_t b[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
		//	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F};
	for(int i = 0; i < num_bytes; ++i){
		*mem = trt[i];
		mem++;
	}
	pattern_wr = MEM_SUCCESS;
}
