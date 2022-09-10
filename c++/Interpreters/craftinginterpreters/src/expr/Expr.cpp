#include "expr/Expr.hpp"

fflang::Expr::~Expr(){};
void fflang::Expr::Vistor::visit_void() {};
void fflang::Expr::accept(Vistor& vistor) const {vistor.visit_void();};