#define DEBUG
#include "src/Runner.hpp"



int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        Runner::run_prompt();
    }
    else if (argc == 2)
    {
        Runner::run_file(argv[1]);
    }
    else
    {
        std::cout << "Usage: fflang [filename]" << std::endl;
    }


    return 0;
}