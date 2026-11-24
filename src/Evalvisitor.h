#pragma once
#ifndef PYTHON_INTERPRETER_EVALVISITOR_H
#define PYTHON_INTERPRETER_EVALVISITOR_H


#include <any>
#include "Python3ParserBaseVisitor.h"
#include <unordered_map>

class EvalVisitor : public Python3ParserBaseVisitor {
    enum class FlowKind { Break, Continue, Return };

    struct FlowSignal {
        FlowKind kind;
        std::any value;
    };

    std::any calc(const std::any& left, const std::any& right, const std::string& op);

    std::unordered_map<std::string, std::any> global; // 存全局变量

	// TODO: override all methods of Python3ParserBaseVisitor
	std::any visitFile_input(Python3Parser::File_inputContext *context) override;

    // std::any visitFuncdef(Python3Parser::FuncdefContext *context) override;

    std::any visitParameters(Python3Parser::ParametersContext *context) override;

    // std::any visitTypedargslist(Python3Parser::TypedargslistContext *context) override;

    std::any visitTfpdef(Python3Parser::TfpdefContext *context) override;

    std::any visitStmt(Python3Parser::StmtContext *context) override;

    std::any visitSimple_stmt(Python3Parser::Simple_stmtContext *context) override;

    std::any visitSmall_stmt(Python3Parser::Small_stmtContext *context) override;

    std::any visitExpr_stmt(Python3Parser::Expr_stmtContext *context) override;

    std::any visitAugassign(Python3Parser::AugassignContext *context) override;

    std::any visitFlow_stmt(Python3Parser::Flow_stmtContext *context) override;

    std::any visitBreak_stmt(Python3Parser::Break_stmtContext *context) override;

    std::any visitContinue_stmt(Python3Parser::Continue_stmtContext *context) override;

    std::any visitReturn_stmt(Python3Parser::Return_stmtContext *context) override;

    std::any visitCompound_stmt(Python3Parser::Compound_stmtContext *context) override;

    // std::any visitIf_stmt(Python3Parser::If_stmtContext *context) override;

    // std::any visitWhile_stmt(Python3Parser::While_stmtContext *context) override;

    std::any visitSuite(Python3Parser::SuiteContext *context) override;

    std::any visitTest(Python3Parser::TestContext *context) override;

    // std::any visitOr_test(Python3Parser::Or_testContext *context) override;

    // std::any visitAnd_test(Python3Parser::And_testContext *context) override;

    // std::any visitNot_test(Python3Parser::Not_testContext *context) override;

    std::any visitComparison(Python3Parser::ComparisonContext *context) override;

    std::any visitComp_op(Python3Parser::Comp_opContext *context) override;

    std::any visitArith_expr(Python3Parser::Arith_exprContext *context) override;

    std::any visitAddorsub_op(Python3Parser::Addorsub_opContext *context) override;

    std::any visitTerm(Python3Parser::TermContext *context) override;

    std::any visitMuldivmod_op(Python3Parser::Muldivmod_opContext *context) override;

    std::any visitFactor(Python3Parser::FactorContext *context) override;

    std::any visitAtom_expr(Python3Parser::Atom_exprContext *context) override;

    std::any visitTrailer(Python3Parser::TrailerContext *context) override;

    std::any visitAtom(Python3Parser::AtomContext *context) override;

    // std::any visitFormat_string(Python3Parser::Format_stringContext *context) override;

    std::any visitTestlist(Python3Parser::TestlistContext *context) override;

    // std::any visitArglist(Python3Parser::ArglistContext *context) override;

    // std::any visitArgument(Python3Parser::ArgumentContext *context) override;
};


#endif//PYTHON_INTERPRETER_EVALVISITOR_H
