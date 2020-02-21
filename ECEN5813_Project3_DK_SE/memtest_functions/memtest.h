/*
 * memtest.h
 *
 *  Created on: Feb 20, 2020
 *      Author: Dhruva
 */

#ifndef MEMTEST_H_
#define MEMTEST_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum{
	SUCCESS = 0,// no error
	FAILED// failure case} mem_status;
} mem_status;

uint8_t* allocate_bytes(uint8_t num_bytes);
void free_allocated(void);
bool verify_memory(void);
void display_memory(uint8_t* mem, uint8_t num_bytes);
void write_memory(uint8_t* mem, uint8_t offset, uint8_t len, uint8_t val);
void invert_block(uint8_t* mem, uint8_t offset, uint8_t num_bytes);
void write_pattern(uint8_t* mem, uint8_t num_bytes, uint8_t seed);
bool compare_pattern(uint8_t* mem, uint8_t num_bytes, uint8_t seed);

#endif /* MEMTEST_H_ */
