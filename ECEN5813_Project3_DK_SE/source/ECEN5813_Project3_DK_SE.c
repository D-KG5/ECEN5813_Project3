/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    ECEN5813_Project3_DK_SE.c
 * @brief   Application entry point.
 */
#include <memtest_functions/memtest.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "led_control.h"
#include "logger.h"
#include "memtest_functions/memtest.h"
#include "global_defines.h"
/* TODO: insert other definitions and declarations here. */
uint8_t *a1; //declare global pointer for malloc array

const uint32_t input_commands[21][4] = {
		{'A', 32, (uint32_t)NULL, (uint32_t)NULL}, { 'M', (uint32_t)NULL, (uint32_t)NULL, (uint32_t)NULL},
		{'P', 32, 143, (uint32_t)NULL}, {'D', 32, (uint32_t)NULL, (uint32_t)NULL},
		{'D', 34, (uint32_t)NULL, (uint32_t)NULL}, {'C', 32, 143, (uint32_t)NULL},
		{'W', 12, 2, 0xFFEE}, {'D', 32, (uint32_t)NULL, (uint32_t)NULL},
		{'C', 32, 143, (uint32_t)NULL}, {'P', 16, 127, (uint32_t)NULL},
		{'D', 16, (uint32_t)NULL, (uint32_t)NULL}, {'C', 16, 127, (uint32_t)NULL},
		{'I', 35, 2, (uint32_t)NULL}, {'I', 9, 2, (uint32_t)NULL},
		{'D', 16, (uint32_t)NULL, (uint32_t)NULL}, {'C', 16, 127, (uint32_t)NULL},
		{'I', 9, 2, (uint32_t)NULL}, {'C', 16, 127, (uint32_t)NULL},
		{'D', 16, (uint32_t)NULL, (uint32_t)NULL}, {'F', (uint32_t)NULL, (uint32_t)NULL, (uint32_t)NULL},
		{'M', (uint32_t)NULL, (uint32_t)NULL, (uint32_t)NULL}
};

// typedef function pointers
typedef void(*funcPtr_t)(void); // generic function ptr wrapper
// specific function pointer defs
typedef uint8_t* (*alloc_b)(uint8_t num_bytes);
typedef void (*free_alloc)(uint8_t* mem);
typedef bool (*ver_mem)(uint8_t* mem);
typedef void (*disp_mem)(uint8_t* mem, uint8_t num_bytes);
typedef void (*wr_mem)(uint8_t* mem, uint8_t offset, uint8_t len, uint16_t val);
typedef void (*inv_blk)(uint8_t* mem, uint8_t offset, uint8_t num_bytes);
typedef void (*wr_patt)(uint8_t* mem, uint8_t num_bytes, uint8_t seed);
typedef bool (*comp_patt)(uint8_t* mem, uint8_t num_bytes, uint8_t seed);

struct commandStruct{
	char const *name;
	funcPtr_t execute;
	char const *help;
};

const struct commandStruct commands[] = {
		{"allocate_bytes", (funcPtr_t)allocate_bytes, "allocating bytes"},
		{"free_allocated", (funcPtr_t)free_allocated, "freeing allocated bytes"},
		{"verify_memory", (funcPtr_t)verify_memory, "verifying memory"},
		{"display_memory", (funcPtr_t)display_memory, "displaying memory"},
		{"write_memory", (funcPtr_t)write_memory, "writing memory to address"},
		{"invert_block", (funcPtr_t)invert_block, "inverting block"},
		{"write_pattern", (funcPtr_t)write_pattern, "writing pattern"},
		{"compare_pattern", (funcPtr_t)compare_pattern, "comparing pattern"},
		{"", 0, ""}
};

void script_parser(uint32_t command, uint32_t arg1, uint32_t arg2, uint32_t arg3){
	switch(command){
	case ((uint32_t)'A'):
		Log_string(&commands[0].name[0]);
		Log_string(&commands[0].help[0]);
		a1 = ((alloc_b)commands[0].execute)(arg1);
		break;
	case ((uint32_t)'F'):
		Log_string(&commands[1].name[0]);
		Log_string(&commands[1].help[0]);
		((free_alloc)commands[1].execute)(a1);
		break;
	case ((uint32_t)'M'):
		Log_string(&commands[2].name[0]);
		Log_string(&commands[2].help[0]);
		bool ver_mem_ret = ((ver_mem)commands[2].execute)(a1);
		Log_integer(ver_mem_ret);
		break;
	case ((uint32_t)'D'):
		Log_string(&commands[3].name[0]);
		Log_string(&commands[3].help[0]);
		((disp_mem)commands[3].execute)(a1, arg1);
		break;
	case ((uint32_t)'W'):
		Log_string(&commands[4].name[0]);
		Log_string(&commands[4].help[0]);
		((wr_mem)commands[4].execute)(a1, arg1, arg2, arg3);
		break;
	case ((uint32_t)'I'):
		Log_string(&commands[5].name[0]);
		Log_string(&commands[5].help[0]);
		((inv_blk)commands[5].execute)(a1, arg1, arg2);
		break;
	case ((uint32_t)'P'):
		Log_string(&commands[6].name[0]);
		Log_string(&commands[6].help[0]);
		((wr_patt)commands[6].execute)(a1, arg1, arg2);
		break;
	case ((uint32_t)'C'):
		Log_string(&commands[7].name[0]);
		Log_string(&commands[7].help[0]);
		bool comp_patt_ret = ((comp_patt)commands[7].execute)(a1, arg1, arg2);
		Log_integer(comp_patt_ret);
		break;
	default:
		break;
	}
}

/*
 * @brief   Application entry point.
 */
static void user_interaction(void){
#ifdef USER_INTERACTION
	getchar();
#endif
}

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    LED_init();
    LED_off(ALL);
    // Testing logging
    Log_enable();

    for(int i = 0; i < 21; i++){
    	script_parser(input_commands[i][0], input_commands[i][1], input_commands[i][2], input_commands[i][3]);
    	user_interaction();
    }

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
