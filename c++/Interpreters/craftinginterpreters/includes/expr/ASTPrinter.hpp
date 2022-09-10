#include "Expr.hpp"

namespace fflang {
    class ASTPrinter : public Expr::Vistor {
        public:
            ASTPrinter() = default;
            ~ASTPrinter() = default;

            void visit_binary(const BinaryExpr& expr) override;
            void visit_unary(const UnaryExpr& expr) override;
            void visit_literal(const LiteralExpr& expr) override;
            void visit_grouping(const GroupingExpr& expr) override;
            void paranthesise(const std::string& name, std::initializer_list<const Expr> exprs) override;
    };
};