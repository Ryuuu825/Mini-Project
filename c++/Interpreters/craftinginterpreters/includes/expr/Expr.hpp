#pragma once 

#include <vector>

namespace fflang {
    class BinaryExpr;
    class UnaryExpr;
    class LiteralExpr;
    class GroupingExpr;


    class Expr {
        public:
        
            class Vistor {
                // vistor is a visitor pattern
                // what is visitor pattern?
                // https://en.wikipedia.org/wiki/Visitor_pattern

                public:
                    ~Vistor() = default;
                    virtual void visit_binary(const BinaryExpr& expr) = 0 ;
                    virtual void visit_unary(const UnaryExpr& expr) = 0 ;
                    virtual void visit_literal(const LiteralExpr& expr) = 0 ;
                    virtual void visit_grouping(const GroupingExpr& expr) = 0 ;
                    virtual void paranthesise(const std::string& name, std::initializer_list<const Expr> exprs) = 0;
            };

            virtual void accept(Vistor& vistor) const;
    }; 
};