#pragma once 

#include "common.hpp"
#include "Expr.hpp"
#include "../Token.hpp"
#include "../types/object.hpp"

#include <any>

namespace fflang {
    class LiteralExpr : public Expr {
        public:
            LiteralExpr(const object_t& obj);
            ~LiteralExpr() = default  ;
            void accept(Vistor& vistor) const ;


            const object_t value; 

    };
}