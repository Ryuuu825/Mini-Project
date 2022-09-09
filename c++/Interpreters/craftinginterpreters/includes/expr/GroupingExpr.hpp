#pragma once 

#include "common.hpp"
#include "Expr.hpp"
#include "../Token.hpp"
#include <memory>

namespace fflang {
    class GroupingExpr : public Expr {
        public:
            GroupingExpr(const std::shared_ptr<Expr>& expr) 
                : expre(expr) {};
            ~GroupingExpr()   = default ;

            void accept(Expr::Vistor& vistor) const  ;

            const std::shared_ptr<Expr> expre;
    };
}