#include "./expr/ASTPrinter.hpp"
#include "./expr/alltypes.hpp"
#include <variant>

void fflang::ASTPrinter::visit_binary(const BinaryExpr& expr)
{
    std::cout << &expr << std::endl;
}
void fflang::ASTPrinter::visit_unary(const UnaryExpr& expr)
{
    std::cout << &expr << std::endl;

}
void fflang::ASTPrinter::visit_literal(const LiteralExpr& expr)
{
    // print the literal value
    if (std::holds_alternative<int>(expr.value))
    {
        std::cout << std::get<int>(expr.value) << std::endl;
    }
    else if (std::holds_alternative<double>(expr.value))
    {
        std::cout << std::get<double>(expr.value) << std::endl;
    }
    else if (std::holds_alternative<std::string>(expr.value))
    {
        std::cout << std::get<std::string>(expr.value) << std::endl;
    }
    else if (std::holds_alternative<null_t>(expr.value))
    {
        std::cout << "null" << std::endl;
    }
    else
    {
        std::cout << "unknown type" << std::endl;
    }
}
void fflang::ASTPrinter::visit_grouping(const GroupingExpr& expr)
{
    std::cout << &expr << std::endl;

}

void fflang::ASTPrinter::paranthesise(const std::string& name, std::initializer_list<const Expr> exprs) 
{
    std::cout << "(" << name << " ";
    for (const auto& expr : exprs) {
        expr.accept(*this);
    }
    std::cout << ')' << std::endl;
}
