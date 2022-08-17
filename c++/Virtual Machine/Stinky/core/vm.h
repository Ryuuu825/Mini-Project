#pragma once
#ifndef VM_H // vm.h
#define VM_H

#include "./includes/instruction.h"
#include "./includes/memory.h"
#include "./includes/register.h"
#include "./includes/vmdef.h"
#include "./includes/api.h"

#include <stdio.h>
#include <stdint.h>
#include <signal.h>
/* unix only */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

#endif // end of vm.h
