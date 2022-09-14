#pragma once 

#include "common.hpp"
#include "Expr.hpp"
#include "../Token.hpp"
#include <memory>

namespace fflang {
    class BinaryExpr : public Expr {
        public:
            BinaryExpr(std::shared_ptr<Expr> lhs, const Token& token,  std::shared_ptr<Expr>rhs);
            ~BinaryExpr()  = default;

            void accept(Expr::Vistor& vistor) const  ;

            const std::shared_ptr<Expr> lhs;
            const std::shared_ptr<Expr> rhs;
            const Token token;

    };
}