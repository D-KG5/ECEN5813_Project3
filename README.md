# ECEN5813_Project3
PES Project 3 for ECEN 5813. By Dhruva Koley and Sagar Eligar

# Contents
- ECEN5813_Project3_DK_SE
  - source
    - ECEN5813_Project3_DK_SE.c: main source file containing command processor and script parser
	- global_defines.h: header file that contains user interaction flag to turn it on and off
	- led_control.c: source file to initialize and control the LED
	- led_control.h: header file for led_control.c
	- logger.c: source file that contains logging utility functions
	- logger.h: header file for logger.c
  - memtest_functions
    - memtest.h: header file containing function definitions for the following memtest script function source files
	- allocate_bytes.c
	- compare_pattern.c
	- display_memory.c
	- free_allocated.c
	- invert_block.c
	- verify_memory.c
	- write_memory.c
	- write_pattern.c
 
# Comments
 - array[0] is byte 0 and so on

# Environment
 - Windows 10
 - MCUXpresso v11.1.0
