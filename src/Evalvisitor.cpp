#include "Evalvisitor.h"
#include <string>
#include <iostream>

std::any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *context) {
    for (auto *statement : context -> stmt()) {
        visit(statement);
    }   
    return {}; // 输入无返回值
}

// std::any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *context) {

// }

// std::any EvalVisitor::visitParameters(Python3Parser::ParametersContext *context)  {

// }

// std::any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *context)  {

// }

std::any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *context)  {
    return context -> getText();
}

std::any EvalVisitor::visitStmt(Python3Parser::StmtContext *context)  {
    // 分类
    if (auto *simple = context -> simple_stmt()) {
        return visit(simple);
    }
    else return visit(context -> compound_stmt());
}

std::any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *context)  {
    return visit(context -> small_stmt());
}

std::any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *context)  {
    if (auto *expr = context -> expr_stmt()) {
        return visit(expr);
    }
    else return visit(context -> flow_stmt());
}

// 这个还要改！
std::any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *context)  {
    visit(context -> testlist(0));
    return {};
}

std::any EvalVisitor::visitAugassign(Python3Parser::AugassignContext *context)  {
    return context -> getText();
}

std::any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *context)  {
    if (auto *break_stmt = context -> break_stmt()) {
        return visit(break_stmt);
    }
    else if (auto *continue_stmt = context -> continue_stmt()) {
        return visit(continue_stmt);
    }
    else return visit(context -> return_stmt());
}

// std::any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *context)  {

// }

// std::any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *context)  {

// }

// std::any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *context)  {

// }

std::any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *context)  {
    if (auto *if_stmt = context -> if_stmt()) {
        return visit(if_stmt);
    }
    else if (auto *while_stmt = context -> while_stmt()) {
        return visit(while_stmt);
    }
    else return visit(context -> funcdef());
}

// std::any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *context)  {

// }

// std::any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *context)  {

// }

// std::any EvalVisitor::visitSuite(Python3Parser::SuiteContext *context)  {
//     if (auto *simple_stmt = context -> simple_stmt()) {
//         return visit(simple_stmt);
//     }
//     // for (auto *statement : context -> stmt()) {
//     //     auto result = visit(statement);
//     //     if (std::any_cast<>)
//     // }
// }

std::any EvalVisitor::visitTest(Python3Parser::TestContext *context)  {
    return visit(context -> or_test());
}

// std::any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *context)  {

// }

// std::any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *context)  {

// }

// std::any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *context)  {

// }

// std::any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *context)  {

// }

std::any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *context)  {
    return context -> getText();
}

// 还要改 不能是long long
std::any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *context)  {
    auto term = context -> term();

    if (term.size() == 1) {
        return visit(term[0]);
    }

    auto res = std::any_cast<long long>(visit(term[0]));

    for (int i = 1; i < term.size(); i++) {
        auto right = std::any_cast<long long>(visit(term[i]));
        auto op = context -> addorsub_op(i - 1) -> getText();

        if (op == "+") {
            res += right;
        }
        else {
            res -= right;
        }
    }
    return res;
}

std::any EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *context)  {
    return context -> getText();
}

// 还要改 不能是long long 以及 除法取模 以及 字符串
std::any EvalVisitor::visitTerm(Python3Parser::TermContext *context)  {
    auto factor = context -> factor();

    if (factor.size() == 1) {
        return visit(factor[0]);
    }

    auto res = std::any_cast<long long>(visit(factor[0]));

    for (int i = 1; i < factor.size(); i++) {
        auto right = std::any_cast<long long>(visit(factor[i]));
        auto op = context -> muldivmod_op(i - 1) -> getText();

        if (op == "*") {
            res *= right;
        }
        // else if (op == "/") {
        //     res -= right;
        // }
        // else if (op == "//") {

        // }
        // else {
        //     res %= right;
        // }
    }
    return res;
}

std::any EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *context)  {
    return context -> getText();
}

// std::any EvalVisitor::visitFactor(Python3Parser::FactorContext *context)  {

// }

// 这个还要改！
std::any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *context)  {
    if (auto *trailer = context -> trailer()) {
        auto *name = context -> atom() -> NAME();
        auto *args = trailer -> arglist();

        if (name && name -> getText() == "print" && args) {
            auto value = visit(args -> argument(0) -> test(0));
            std::cout << std::any_cast<long long>(value) << '\n';
        }

        return {};
    }
    else {
        return visit(context -> atom());
    }
}

std::any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *context)  {
    if (auto *arg = context -> arglist()) {
        return visit(arg);
    }
    return {};
}

// 这个还要改！
std::any EvalVisitor::visitAtom(Python3Parser::AtomContext *context)  {
    if (auto *number = context -> NUMBER()) {
        return std::stoll(number -> getText());
    }
    return {};
}

// std::any EvalVisitor::visitFormat_string(Python3Parser::Format_stringContext *context)  {

// }

// 这个还要改！
std::any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *context)  {
    return visit(context -> test(0));
}

// std::any EvalVisitor::visitArglist(Python3Parser::ArglistContext *context)  {

// }

// std::any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *context)  {

// }