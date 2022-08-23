#pragma once 

namespace fflang {
    class BinaryExpr;
    class UnaryExpr;
    class LiteralExpr;
    class GroupingExpr;


    class Expr {
        public:
            virtual ~Expr() = default;
        
            class Vistor {
                // vistor is a visitor pattern
                // what is visitor pattern?
                // https://en.wikipedia.org/wiki/Visitor_pattern

                public:
                    ~Vistor() = default;
                    void visit_binary(const BinaryExpr& expr);
                    void visit_unary(const UnaryExpr& expr);
                    void visit_literal(const LiteralExpr& expr);
                    void visit_grouping(const GroupingExpr& expr);
            };

            virtual void accept(Vistor& vistor) = 0;

    }; 
};