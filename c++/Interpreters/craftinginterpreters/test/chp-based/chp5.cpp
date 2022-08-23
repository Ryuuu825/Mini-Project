#define TEST
#include "../test_script.hpp"
#include "expr/Expr.hpp"
#include "expr/alltypes.hpp"
#include <iostream>
#include <memory>

typedef std::variant<null_t, int, double, std::string> object_t;
void test_token_num(const char* file , int expected)
{
    
    Runner::run_file(file);
    assert(Runner::has_error() == false );
    assert(Runner::get_token_num() == expected );
}

int main(void)
{
    //fflang::LiteralExpr e = {1};
    auto ex = std::make_unique<fflang::LiteralExpr>(null_t());
    fflang::Expr::Vistor vistor = fflang::Expr::Vistor();
    ex->accept(vistor);
    return 0;
}

