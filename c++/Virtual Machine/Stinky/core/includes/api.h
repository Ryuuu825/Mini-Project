enum trap_code
{
    GETC = 0x20,
    OUT = 0x21,
    PUTS = 0x22,
    IN = 0x23,      // get one char, with echoed onto stdOut
    PUTSP = 0x24,   //  out a byte string
    HALT = 0x25
};

#include <iostream>
#include "vmdef.h"
#include "register.h"
u16 vm_getc()
{
    char c = 0;
    std::cin.get(&c , 1);
    return (u16) c; // return a copy value of char input
}

void vm_putc()
{
    extern u16 reg[16];
    char data = reg[R_R0];
    std::cout << data;
    std::cout.flush();
}

void 