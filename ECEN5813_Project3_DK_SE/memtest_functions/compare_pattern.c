/*
 * compare_pattern.c
 *
 *  Created on: Feb 20, 2020
 *      Author: Dhruva
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "MKL25Z4.h"
#include <stdlib.h>
#include "global_defines.h"
#include "fsl_debug_console.h"
#include "memtest.h"
#include "source/logger.h"
#include "memtest.h"

mem_status_t comp_m;
bool ret = false;

bool compare_pattern(uint8_t* mem, uint8_t num_bytes, uint8_t seed){
	if(num_bytes <= MAX_SIZE){
		uint8_t* new;
		new = (uint8_t*)malloc(num_bytes*sizeof(uint8_t));
		new= gen_pattern(num_bytes,seed);
		for(int i=0;i<num_bytes;i++){
			while(mem[i] != new[i]){
				Log_string("False");
				ret = false;
				comp_m = MEM_FAILED;
				if(comp_m == MEM_SUCCESS){
					LED_flash(GREEN);
				} else{
					LED_flash(RED);
				}
				return ret;
			}
		}
		ret = true;
		comp_m = MEM_SUCCESS;
		Log_string("True");
	}else{
		comp_m = MEM_FAILED;
	}

	if(comp_m == MEM_SUCCESS){
		LED_flash(GREEN);
	} else{
		LED_flash(RED);
	}
	return ret;
}
