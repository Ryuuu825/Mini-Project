#include "./expr/UnaryExpr.hpp"

void fflang::UnaryExpr::accept(Expr::Vistor& vistor) const
{
    vistor.visit(*this);
}

fflang::UnaryExpr::UnaryExpr(const Token& token , std::shared_ptr<Expr> expr)
                : token(token) , expr(std::move(expr)) {}; 
