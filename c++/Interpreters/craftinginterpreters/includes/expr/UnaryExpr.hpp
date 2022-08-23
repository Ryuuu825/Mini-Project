#pragma once 

#include "common.hpp"
#include "Expr.hpp"
#include "../Token.hpp"
#include "../types/object.hpp"
#include <memory>
#include <any>

namespace fflang {
    class UnaryExpr : public Expr {
        public:
            UnaryExpr(const Token& token , std::unique_ptr<Expr> expr)
                : token(token) , expr(std::move(expr)) {}; 
            ~UnaryExpr()  = default ;

            void accept(Expr::Vistor& vistor) override ;

            const Token token;
            const std::unique_ptr<Expr> expr;

    };
}