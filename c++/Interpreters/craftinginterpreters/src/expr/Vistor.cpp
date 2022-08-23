#include "./expr/Expr.hpp"
#include "./expr/alltypes.hpp"
#include <variant>

void fflang::Expr::Vistor::visit_binary(const BinaryExpr& expr)
{
    std::cout << &expr << std::endl;
}
void fflang::Expr::Vistor::visit_unary(const UnaryExpr& expr)
{
    std::cout << &expr << std::endl;

}
void fflang::Expr::Vistor::visit_literal(const LiteralExpr& expr)
{
    std::cout << expr.value.index() << std::endl;
}
void fflang::Expr::Vistor::visit_grouping(const GroupingExpr& expr)
{
    std::cout << &expr << std::endl;

}