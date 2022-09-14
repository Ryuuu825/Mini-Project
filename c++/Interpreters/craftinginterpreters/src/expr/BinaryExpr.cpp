#include "expr/BinaryExpr.hpp"

fflang::BinaryExpr::BinaryExpr(std::shared_ptr<Expr> lhs, const Token& token,  std::shared_ptr<Expr>rhs) 
    : lhs(std::move(lhs))  , rhs(std::move(rhs)) , token(token) {};

void fflang::BinaryExpr::accept(Expr::Vistor& vistor) const  
{
    vistor.visit(*this);
}
