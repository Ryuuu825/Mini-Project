#define TEST
#include "../test_script.hpp"
#include <iostream>


void test_token_num(const char* file , int expected)
{
    
    Runner::run_file(file);
    assert(Runner::has_error() == false );
    assert(Runner::get_token_num() == expected );
}

int main(void)
{
    test_has_error("./chp4.ff" , false);
    test_token_num("./chp4.ff" , 15);
    return 0;
}

