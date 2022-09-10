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
                    ~Vistor();
                    void visit_void();
                    #pragma GCC diagnostic push
                    #pragma GCC diagnostic ignored "-Wunused-parameter"
                        virtual void visit_binary(const BinaryExpr& expr) {} ;
                        virtual void visit_unary(const UnaryExpr& expr) {} ;
                        virtual void visit_literal(const LiteralExpr& expr) {} ;
                        virtual void visit_grouping(const GroupingExpr& expr) {} ;
                        virtual void paranthesise(const std::string& name, std::initializer_list<const Expr> exprs) {};
                    #pragma GCC diagnostic pop
            };

            virtual void accept(Vistor& vistor) const;
            ~Expr();
    }; 
};