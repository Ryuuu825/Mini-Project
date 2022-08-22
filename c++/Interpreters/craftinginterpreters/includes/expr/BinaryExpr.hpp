#pragma once 

#include "common.hpp"
#include "Expr.hpp"
#include "../Token.hpp"
#include <memory>

namespace fflang {
    class BinaryExpr : public Expr {
        public:
            BinaryExpr(std::unique_ptr<Expr> lhs, const Token& token,  std::unique_ptr<Expr>rhs) ;
            ~BinaryExpr() override ;

            void accept(Expr::Vistor& vistor) override ;

            const std::unique_ptr<Expr> lhs;
            const std::unique_ptr<Expr> rhs;
            const Token token;

    };
}