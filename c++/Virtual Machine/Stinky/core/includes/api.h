
#pragma once 

enum trap_code
{
    GETC = 0x20,
    OUT = 0x21,
    PUTS = 0x22,
    HALT = 0x23
};

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
/* unix only */
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>


#include "vmdef.h"
#include "register.h"
#include "memory.h"

u16 swap16(u16 x);
u16 vm_getc();
void vm_putc();
void vm_out_string() ;
void vm_halt();
void read_image_from_file(FILE* file);
int read_image(const char* image_path);
void disable_input_buffering();
void restore_input_buffering();