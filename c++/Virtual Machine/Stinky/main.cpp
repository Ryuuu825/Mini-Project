#include "core/vm.h"
#include <iostream>

/* main memory */
u16 mem[UINT16_MAX] = {0};
/* register */
u16 reg[16] = {0};

bool running = 1;

struct termios original_tio;


int main(int argc , char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./vm {file} " << std::endl;
        exit(-1);
    }

    read_image(argv[1]);
    disable_input_buffering();

    u16* instruction = &(mem[START]);
    while (running && *instruction)
    {
        u16 op_bit = getop(*instruction);
        switch (op_bit)
        {
            case OP_BR :    /* branch */
                std::cout << "branch" << std::endl;
                branch(*instruction);
                break;
            case OP_ADD:    /* add  */
                std::cout << "add" << std::endl;
                add(*instruction);
                break;
            case OP_LD:    /* load */
                std::cout << "load" << std::endl;
                load(*instruction);
                break;
            case OP_ST:    /* store */
                std::cout << "store" << std::endl;

                store(*instruction);
                break;
            case OP_JSR:    /* jump register */
                std::cout << "jump register" << std::endl;
                jump(*instruction);
                break;
            case OP_AND:    /* bitwise and */
                std::cout << "bitwise and" << std::endl;
                op_and(*instruction);
                break;
            case OP_LDR:    /* load register */
                std::cout << "load register" << std::endl;
                break;
            case OP_STR:    /* store register */
                std::cout << "store register" << std::endl;
                store_register(*instruction);
                break;
            case OP_RTI:    /* unused */
                std::cout << "unused" << std::endl;
                break;
            case OP_NOT:    /* bitwise not */
                std::cout << "bitwise not" << std::endl;
                op_not(*instruction);
                break;
            case OP_LDI:    /* load indirect */
                std::cout << "load indirect" << std::endl;
                ldi(*instruction);
                break;
            case OP_STI:    /* store indirect */
                std::cout << "store indirect" << std::endl;
                store_indirect(*instruction);
                break;
            case OP_JMP:    /* jump */
                std::cout << "jump" << std::endl;
                jump(*instruction);
                break;
            case OP_RES:    /* reserved (unused) */
                std::cout << "reserved (unused)" << std::endl;
                break;
            case OP_LEA:    /* load effective address */
                std::cout << "load effective address" << std::endl;
                lea(*instruction);
                break;
            case OP_TRAP:    /* execute trap */
                std::cout << "execute trap" << std::endl;
                switch (*instruction & 0xFF)
                {
                    case trap_code::GETC:
                        std::cout << "getc" << std::endl;
                        vm_getc();
                        break;
                    case trap_code::PUTS:
                        std::cout << "puts" << std::endl;
                        vm_out_string();
                        break;
                    case trap_code::HALT:
                        vm_halt();
                        break;
                    default:
                        std::cout << "unknown trap" << std::endl;
                        break;
                }
                break;
            default:
                std::cout << "Unknown instruction" << *instruction << std::endl;
                vm_halt();
                break;

        }
        instruction++;
    }

    vm_halt();


    
}
 