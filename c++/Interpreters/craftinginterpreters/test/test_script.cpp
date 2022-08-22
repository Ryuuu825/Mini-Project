// read an files and check the output 

#include "test_script.hpp"
void test_has_error(const char* file , bool expected)
{
    Runner::run_file(file);
    assert(Runner::has_error() == expected );
}

