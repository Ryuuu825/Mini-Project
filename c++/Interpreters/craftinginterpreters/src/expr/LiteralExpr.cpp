#include "./expr/LiteralExpr.hpp"

void fflang::LiteralExpr::accept(Expr::Vistor& vistor) const
{
    vistor.visit(*this);
}

fflang::LiteralExpr::LiteralExpr(const object_t& obj) 
    : value(obj) {};
