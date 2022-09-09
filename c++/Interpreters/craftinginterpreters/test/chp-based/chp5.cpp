#define TEST
#include "../test_script.hpp"
#include "expr/ASTPrinter.hpp"
#include "expr/alltypes.hpp"
#include <iostream>
#include <memory>

using namespace fflang;

void test_token_num(const char* file , int expected)
{
    
    Runner::run_file(file);
    assert(Runner::has_error() == false );
    assert(Runner::get_token_num() == expected );
}

int main(void)
{
    //fflang::LiteralExpr e = {1};
    /* Expr expression = new Expr.Binary(
        new Expr.Unary(
            new Token(TokenType.MINUS, "-", null, 1),
            new Expr.Literal(123)),
        new Token(TokenType.STAR, "*", null, 1),
        new Expr.Grouping(
            new Expr.Literal(45.67)));
    */
    // Expr expression = std::make_shared<BinaryExpr>(
    //     std::make_shared<UnaryExpr>(
    //         Token(TokenType::MINUS, "-", nullptr, 1),
    //         std::make_shared<LiteralExpr>(object_t(123))
    //     ),
    //     Token(TokenType::STAR, "*", nullptr, 1),
    //     std::make_shared<GroupingExpr>(
    //         std::make_shared<LiteralExpr>(object_t(45.67))
    //     )
    // );
    fflang::ASTPrinter vistor = fflang::ASTPrinter(); 
    
    return 0;
}

