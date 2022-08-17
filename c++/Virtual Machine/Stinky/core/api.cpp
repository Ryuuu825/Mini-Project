#include "./includes/api.h"

u16 swap16(u16 x)
{
    return (x << 8) | (x >> 8);
}

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

void vm_out_string() 
{
    extern u16 reg[16];
    extern u16 mem[UINT16_MAX];

    u16* c = mem + reg[R_R0];
    while(*c)
    {
        char ca = *(c) & 0xFF;
        putc(ca , stdout);
        ca = (*c) >> 8;
        if (c) putc(ca , stdout);
    }
}

void vm_halt()
{
    std::cout << "Halt" << std::endl ;
    extern int running;
    running = 0;
    restore_input_buffering();
}


void read_image_from_file(FILE* file)
{
    extern u16 mem[UINT16_MAX];
    u16 origin; 
    fread(&origin , sizeof(origin), 1 , file);
    origin = swap16(origin);


    u16 max_read = MEMORY_MAX - origin;
    u16* p = mem + origin; 
    size_t read = fread(p , sizeof(origin) , max_read , file);

    while(read-- > 0)
    {
        *p = swap16(*p);
        ++p; 
    }
}

int read_image(const char* image_path)
{
    FILE* file = fopen(image_path, "rb");
    if (!file) { return 0; };
    read_image_from_file(file);
    fclose(file);
    return 1;
}

void disable_input_buffering()
{
    extern struct termios original_tio;
    tcgetattr(STDIN_FILENO, &original_tio);
    struct termios new_tio = original_tio;
    new_tio.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void restore_input_buffering()
{
    extern struct termios original_tio;
    tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}