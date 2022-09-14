#include "./expr/ASTPrinter.hpp"
#include "./expr/alltypes.hpp"


void fflang::ASTPrinter::visit(const BinaryExpr& expr)
{
    paranthesise(  expr.token.literal , {*(expr.lhs.get())  , *(expr.rhs.get())} );
}
void fflang::ASTPrinter::visit(const UnaryExpr& expr)
{
    paranthesise( expr.token.literal , {*(expr.expr.get())} );
}
void fflang::ASTPrinter::visit(const LiteralExpr& expr)
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
void fflang::ASTPrinter::visit(const GroupingExpr& expr)
{
    paranthesise("group", {*(expr.expre.get())});
}

void fflang::ASTPrinter::paranthesise(const std::string& name, std::initializer_list<const Expr> exprs) 
{
    std::cout << "(" << name << " ";
    for (const auto& expr : exprs) {
        expr.accept(*this);
    }
    std::cout << ')' << std::endl;
}
