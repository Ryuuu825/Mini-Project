#pragma once 

#include "alltypes.hpp"
namespace fflang {
    class Expr {
        public:
            virtual ~Expr() = default;
        
            class Vistor {
                // vistor is a visitor pattern
                // what is visitor pattern?
                // https://en.wikipedia.org/wiki/Visitor_pattern

                public:
                    virtual ~Vistor() = default;
                    void visit_binary(const Expr& expr);
            };

            virtual void accept(Vistor& vistor) = 0;

    }; 
};