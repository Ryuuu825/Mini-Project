#include "./expr/LiteralExpr.hpp"

void fflang::LiteralExpr::accept(Expr::Vistor& vistor) const
{
    vistor.visit_literal(*this);
}

fflang::LiteralExpr::LiteralExpr(const object_t& obj) 
    : value(obj) {};
