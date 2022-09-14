#include "Expr.hpp"

namespace fflang {
    class ASTPrinter : public Expr::Vistor {
        public:
            ASTPrinter() = default;
            ~ASTPrinter() = default;
            
            void visit(const BinaryExpr& expr) override;
            void visit(const UnaryExpr& expr) override;
            void visit(const LiteralExpr& expr) override;
            void visit(const GroupingExpr& expr) override;
            void paranthesise(const std::string& name, std::initializer_list<const Expr> exprs) override;
    };
};