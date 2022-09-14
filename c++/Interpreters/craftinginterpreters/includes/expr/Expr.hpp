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
                        virtual void visit(const BinaryExpr& expr) = 0;
                        virtual void visit(const UnaryExpr& expr) = 0;
                        virtual void visit(const LiteralExpr& expr)  = 0;
                        virtual void visit(const GroupingExpr& expr)  = 0;
                        virtual void paranthesise(const std::string& name, std::initializer_list<const Expr> exprs) = 0;
                    #pragma GCC diagnostic pop
            };

            virtual void accept(Vistor& vistor) const;
            ~Expr();
    }; 
};