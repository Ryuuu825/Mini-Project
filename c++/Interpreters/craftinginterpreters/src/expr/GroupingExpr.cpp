#include "expr/GroupingExpr.hpp"

fflang::GroupingExpr::GroupingExpr(const std::shared_ptr<Expr>& expr) 
    : expre(expr) {};

void fflang::GroupingExpr::accept(Expr::Vistor& vistor) const  
{
    vistor.visit(*this);
}
