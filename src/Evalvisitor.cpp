#include "Evalvisitor.h"
#include "int2048.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <utility>

using sjtu::int2048;
struct None {}; 

static double int2048ToDouble(const sjtu::int2048& value) {
    std::ostringstream text;
    text << value;
    return std::stod(text.str());
}

std::any EvalVisitor::calc(const std::any& left, const std::any& right, const std::string& op) {
    // 运算：+ - * /  // %
    if (op == "+") {
        if (auto *leftStr = std::any_cast<std::string>(&left)) {
            auto *rightStr = std::any_cast<std::string>(&right);
            std::string res = *leftStr + *rightStr;
            return res;
        }
        std::any a = left;
        std::any b = right;
        if (a.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(a);
            a = int2048(flag ? 1LL : 0LL);
        }
        if (b.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(b);
            b = int2048(flag ? 1LL : 0LL);
        }
        if (a.type() == typeid(double) || b.type() == typeid(double)) {
            double x, y;
            if (a.type() == typeid(double)) x = std::any_cast<double>(a);
            else x = int2048ToDouble(std::any_cast<int2048>(a));
            if (b.type() == typeid(double)) y = std::any_cast<double>(b);
            else y = int2048ToDouble(std::any_cast<int2048>(b));
            return x + y;
        }
        int2048 x = std::any_cast<int2048>(a);
        int2048 y = std::any_cast<int2048>(b);
        return x + y;
    }   
    if (op == "-") {
        std::any a = left;
        std::any b = right;
        if (a.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(a);
            a = int2048(flag ? 1LL : 0LL);
        }
        if (b.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(b);
            b = int2048(flag ? 1LL : 0LL);
        }
        if (a.type() == typeid(double) || b.type() == typeid(double)) {
            double x, y;
            if (a.type() == typeid(double)) x = std::any_cast<double>(a);
            else x = int2048ToDouble(std::any_cast<int2048>(a));
            if (b.type() == typeid(double)) y = std::any_cast<double>(b);
            else y = int2048ToDouble(std::any_cast<int2048>(b));
            return x - y;
        }
        int2048 x = std::any_cast<int2048>(a);
        int2048 y = std::any_cast<int2048>(b);
        return x - y;
    }   
    if (op == "*") {
        std::any a = left;
        std::any b = right;
        if (a.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(a);
            a = int2048(flag ? 1LL : 0LL);
        }
        if (b.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(b);
            b = int2048(flag ? 1LL : 0LL);
        }

        if (auto *leftStr = std::any_cast<std::string>(&left)) {
            std::string res = "";
            int2048 cnt = std::any_cast<int2048>(b);
            while (cnt > 0) {
                cnt -= int2048(1LL);
                res += *leftStr;
            }
            return res;
        }
        if (auto *rightStr = std::any_cast<std::string>(&right)) {
            std::string res = "";
            int2048 cnt = std::any_cast<int2048>(a);
            while (cnt > 0) {
                cnt -= int2048(1LL);
                res += *rightStr;
            }
            return res;
        }

        if (a.type() == typeid(double) || b.type() == typeid(double)) {
            double x, y;
            if (a.type() == typeid(double)) x = std::any_cast<double>(a);
            else x = int2048ToDouble(std::any_cast<int2048>(a));
            if (b.type() == typeid(double)) y = std::any_cast<double>(b);
            else y = int2048ToDouble(std::any_cast<int2048>(b));
            return x * y;
        }
        int2048 x = std::any_cast<int2048>(a);
        int2048 y = std::any_cast<int2048>(b);
        return x * y;
    }   
    if (op == "/") {
        std::any a = left;
        std::any b = right;
        if (a.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(a);
            a = flag ? 1.0 : 0.0;
        }
        if (b.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(b);
            b = flag ? 1.0 : 0.0;
        }
        double x, y;
        if (a.type() == typeid(double)) x = std::any_cast<double>(a);
        else x = int2048ToDouble(std::any_cast<int2048>(a));
        if (b.type() == typeid(double)) y = std::any_cast<double>(b);
        else y = int2048ToDouble(std::any_cast<int2048>(b));
        return x / y;
    }
    if (op == "//") {
        std::any a = left;
        std::any b = right;
        if (a.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(a);
            a = int2048(flag ? 1LL : 0LL);
        }
        if (b.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(b);
            b = int2048(flag ? 1LL : 0LL);
        }
        if (a.type() == typeid(double) || b.type() == typeid(double)) {
            double x, y;
            if (a.type() == typeid(double)) x = std::any_cast<double>(a);
            else x = int2048ToDouble(std::any_cast<int2048>(a));
            if (b.type() == typeid(double)) y = std::any_cast<double>(b);
            else y = int2048ToDouble(std::any_cast<int2048>(b));
            return std::floor(x / y);
        }
        int2048 x = std::any_cast<int2048>(a);
        int2048 y = std::any_cast<int2048>(b);
        return x / y;
    }
    if (op == "%") {
        std::any a = left;
        std::any b = right;
        if (a.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(a);
            a = int2048(flag ? 1LL : 0LL);
        }
        if (b.type() == typeid(bool)) {
            bool flag = std::any_cast<bool>(b);
            b = int2048(flag ? 1LL : 0LL);
        }
        if (a.type() == typeid(double) || b.type() == typeid(double)) {
            double x, y;
            if (a.type() == typeid(double)) x = std::any_cast<double>(a);
            else x = int2048ToDouble(std::any_cast<int2048>(a));
            if (b.type() == typeid(double)) y = std::any_cast<double>(b);
            else y = int2048ToDouble(std::any_cast<int2048>(b));

            double remainder = std::fmod(x, y);
            if (remainder == 0.0) {
                return std::copysign(0.0, y);
            }
            if ((remainder < 0.0) != (y < 0.0)) {
                remainder += y;
            }
            return remainder;
        }
        int2048 x = std::any_cast<int2048>(a);
        int2048 y = std::any_cast<int2048>(b);
        return x % y;
    }
    return {};
}

std::any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *context) {
    for (auto *statement : context -> stmt()) {
        visit(statement);
    }   
    return {}; // 输入无返回值
}

std::any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *context) {
    // funcdef: 'def' NAME parameters ':' suite;
    std::string name = context -> NAME() -> getText();
    function[name].suite = context -> suite();
    
    // 参数表
    if (auto *args = context -> parameters() -> typedargslist()) {
        for (auto *param : args -> tfpdef()) {
            function[name].parameters.push_back(param -> NAME() -> getText());
        }
    }
    return {}; 
}

std::any EvalVisitor::visitParameters(Python3Parser::ParametersContext *context)  {
    if (auto *type = context -> typedargslist()) {
        return visit(type);
    }
    return {};
}

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

std::any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *context)  {
    if (auto *op = context -> augassign()) {  // augassign: ('+=' | '-=' | '*=' | '/=' | '//=' | '%=' )
        std::string opStr = op -> getText();
        opStr.pop_back();

        auto left_testlist = context -> testlist(0) -> test();
        auto right_testlist = context -> testlist(1) -> test();
        
        std::vector<std::pair<std::string, std::any>> scope_temp;
        std::vector<std::pair<std::string, std::any>> global_temp;
        for (size_t i = 0; i < left_testlist.size(); i++) {
            auto left_name = left_testlist[i] -> getText();
            // 这边要注意先读旧值！
            std::any left;
            bool flag = 0;
            if (scope.size()) {
                auto &u = scope.top();
                if (u.find(left_name) != u.end()) {
                    left = u[left_name];
                    flag = 1; // 局部变量
                }
            }
            if (!flag) {
                left = global[left_name];
            }
            auto right = visit(right_testlist[i]);
            if (flag) {
                scope_temp.push_back({left_name, calc(left, right, opStr)});
            }
            else {
                global_temp.push_back({left_name, calc(left, right, opStr)});
            }
        }
        for (auto u : scope_temp) {
            scope.top()[u.first] = u.second;
        }
        for (auto u : global_temp) {
            global[u.first] = u.second;
        }
        
        return {};
    } 
    else if (!context -> ASSIGN().empty()) {  // 赋值
        auto testlist = context -> testlist();
        auto value = visit(testlist.back());

        if (auto *Value = std::any_cast<std::vector<std::any>>(&value)) {
            auto targets = testlist.front() -> test();
            for (int i = 0; i < targets.size(); i++) {
                auto name = targets[i] -> getText();
                if (scope.size()) {
                    auto &u = scope.top();
                    if (u.find(name) != u.end()) {
                        u[name] = (*Value)[i];
                        continue;
                    }
                }
                if (global.find(name) != global.end() || scope.empty()) {
                    global[name] = (*Value)[i];    
                }
                else {
                    auto &u = scope.top();
                    u[name] = (*Value)[i];
                }
            }
            return {};
        }

        for (int i = testlist.size() - 1; i > 0; i--) {
            auto name = testlist[i-1] -> getText();
            if (scope.size()) {
                auto &u = scope.top();
                if (u.find(name) != u.end()) {
                    u[name] = value;
                    continue;
                }
            }
            if (global.find(name) != global.end() || scope.empty()) {
                global[name] = value;    
            }
            else {
                auto &u = scope.top();
                u[name] = value;
            }
        }
        return {};
    } 
    else {
        return visit(context -> testlist(0));
    }
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

std::any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *) {
    return FlowSignal{FlowKind::Break, {}};
}

std::any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *) {
    return FlowSignal{FlowKind::Continue, {}};
}

std::any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *context) {
    if (auto *values = context -> testlist()) { // 有返回值
        return FlowSignal{FlowKind::Return, visit(values)};
    }
    return FlowSignal{FlowKind::Return, {}};
}

std::any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *context)  {
    if (auto *if_stmt = context -> if_stmt()) {
        return visit(if_stmt);
    }
    else if (auto *while_stmt = context -> while_stmt()) {
        return visit(while_stmt);
    }
    else return visit(context -> funcdef());
}

bool toBool(const std::any& value) {
    if (auto *flag = std::any_cast<bool>(&value)) {
        return *flag;
    }   
    if (auto *integer = std::any_cast<int2048>(&value)) {
        return *integer != int2048(0LL);
    }
    if (auto *number = std::any_cast<double>(&value)) {
        return *number != 0.0;
    }
    if (auto *text = std::any_cast<std::string>(&value)) {
        return !text -> empty();
    }
    if (std::any_cast<None>(&value)) {
        return false;
    }
    return false;
}

std::string toStr(const std::any& value) {
    if (auto *flag = std::any_cast<bool>(&value)) {
        return *flag ? "True" : "False";
    }   
    if (auto *integer = std::any_cast<int2048>(&value)) {
        std::ostringstream text;
        text << *integer;
        return text.str();
    }
    if (auto *number = std::any_cast<double>(&value)) {
        return std::to_string(*number);
    }
    if (auto *text = std::any_cast<std::string>(&value)) {
        return *text;
    }
    if (std::any_cast<None>(&value)) {
        return "None";
    }
    return "";
}

std::any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *context)  {
    // if_stmt: 'if' test ':' suite ('elif' test ':' suite)* ('else' ':' suite)?;
    auto tests = context -> test();
    for (int i = 0; i < tests.size(); i++) {
        if (toBool(visit(tests[i]))) {
            return visit(context -> suite(i));
        }
    }
    if (auto *Else = context -> ELSE()) {
        return visit(context -> suite(tests.size()));
    }
    return {};
}

std::any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *context)  {
    // while_stmt: 'while' test ':' suite;
    while (toBool(visit(context -> test()))) {
        auto res = visit(context -> suite());
        if (auto signal = std::any_cast<FlowSignal>(&res)) {
            if (signal -> kind == FlowKind::Break) {
                return {};
            }
            else if (signal -> kind == FlowKind::Continue) {
                continue;
            }
            else {
                return res;
            }
        }
    }
    return {};
}

std::any EvalVisitor::visitSuite(Python3Parser::SuiteContext *context) {
    if (auto *simple_stmt = context -> simple_stmt()) {
        return visit(simple_stmt);
    }
    for (auto *statement : context -> stmt()) {
        auto result = visit(statement);
        if (std::any_cast<FlowSignal>(&result)) {
            return result;
        }
    }
    return {};
}

std::any EvalVisitor::visitTest(Python3Parser::TestContext *context)  {
    return visit(context -> or_test());
}

std::any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *context)  {
    auto and_tests = context -> and_test();
    // 一定要特判！！ 否则print(1)都会输出True
    if (and_tests.size() == 1) {
        return visit(and_tests[0]);
    }
    for (int i = 0; i < and_tests.size(); i++) {
        if (toBool(visit(and_tests[i]))) return true;
    }
    return false;
}

std::any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *context)  {
    auto not_tests = context -> not_test();
    if (not_tests.size() == 1) {
        return visit(not_tests[0]);
    }
    for (int i = 0; i < not_tests.size(); i++) {
        if (!toBool(visit(not_tests[i]))) return false;
    }
    return true;
}

std::any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *context)  {
    if (auto *notTest = context -> not_test()) {
        return !toBool(visit(notTest));
    }
    else return visit(context -> comparison());
}

bool compareValues(const std::any& left, const std::any& right, const std::string& op) {
    // op：'<' | '>' | '==' | '>=' | '<=' | '!=';
    bool leftNone = std::any_cast<None>(&left) != nullptr;
    bool rightNone = std::any_cast<None>(&right) != nullptr;

    if (leftNone || rightNone) {
        if (op == "==") {
            return (leftNone && rightNone);
        }
        else {
            return false;
        }
    }

    if (auto *leftStr = std::any_cast<std::string>(&left)) {
        if (auto *rightStr = std::any_cast<std::string>(&right)) {
            if (op == "<") {
                return static_cast<bool>(*leftStr < *rightStr);
            }
            if (op == ">") {
                return static_cast<bool>(*leftStr > *rightStr);
            }
            if (op == "==") {
                return static_cast<bool>(*leftStr == *rightStr);
            }
            if (op == ">=") {
                return static_cast<bool>(*leftStr >= *rightStr);
            }
            if (op == "<=") {
                return static_cast<bool>(*leftStr <= *rightStr);
            }
            if (op == "!=") {
                return static_cast<bool>(*leftStr != *rightStr);
            }
        }
        else {
            // "1" == 1
            return false;
        }
    }
    // 1 == "1"
    if (auto *rightStr = std::any_cast<std::string>(&right)) {
        return false;
    }
    std::any a = left;
    std::any b = right;
    if (a.type() == typeid(bool)) {
        bool flag = std::any_cast<bool>(a);
        a = int2048(flag ? 1LL : 0LL);
    }
    if (b.type() == typeid(bool)) {
        bool flag = std::any_cast<bool>(b);
        b = int2048(flag ? 1LL : 0LL);
    }
    if (a.type() == typeid(double) || b.type() == typeid(double)) {
        double x, y;
        if (a.type() == typeid(double)) x = std::any_cast<double>(a);
        else x = int2048ToDouble(std::any_cast<int2048>(a));
        if (b.type() == typeid(double)) y = std::any_cast<double>(b);
        else y = int2048ToDouble(std::any_cast<int2048>(b));
        if (op == "<") {
            return static_cast<bool>(x < y);
        }
        if (op == ">") {
            return static_cast<bool>(x > y);
        }
        if (op == "==") {
            return static_cast<bool>(x == y);
        }
        if (op == ">=") {
            return static_cast<bool>(x >= y);
        }
        if (op == "<=") {
            return static_cast<bool>(x <= y);
        }
        if (op == "!=") {
            return static_cast<bool>(x != y);
        }
    }
    int2048 x = std::any_cast<int2048>(a);
    int2048 y = std::any_cast<int2048>(b);
    if (op == "<") {
        return static_cast<bool>(x < y);
    }
    if (op == ">") {
        return static_cast<bool>(x > y);
    }
    if (op == "==") {
        return static_cast<bool>(x == y);
    }
    if (op == ">=") {
        return static_cast<bool>(x >= y);
    }
    if (op == "<=") {
        return static_cast<bool>(x <= y);
    }
    if (op == "!=") {
        return static_cast<bool>(x != y);
    }
    return false;
}

std::any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *context)  {
    auto comp_op = context -> comp_op();
    if (comp_op.empty()) {
        return visit(context -> arith_expr(0));
    }
    else {
        auto left = visit(context -> arith_expr(0));
        for (int i = 0; i < comp_op.size(); i++) {
            auto op = context -> comp_op(i) -> getText();
            auto right = visit(context -> arith_expr(i + 1));
            if (!compareValues(left, right, op)) return false;
            left = right;
        }
        return true;
    }
}

std::any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *context)  {
    return context -> getText();
}

std::any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *context)  {
    auto term = context -> term();
    auto res = visit(term[0]);
    if (term.size() == 1) return res;
    for (std::size_t i = 1; i < term.size(); i++) {
        auto right = visit(term[i]);
        auto op = context -> addorsub_op(i - 1) -> getText();
        res = calc(res, right, op);
    }
    return res;
}

std::any EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *context)  {
    return context -> getText();
}

std::any EvalVisitor::visitTerm(Python3Parser::TermContext *context)  {
    auto factor = context -> factor();
    auto res = visit(factor[0]);
    if (factor.size() == 1) return res;
    for (std::size_t i = 1; i < factor.size(); i++) {
        auto right = visit(factor[i]);
        auto op = context -> muldivmod_op(i - 1) -> getText();
        res = calc(res, right, op);
    }
    return res;
}

std::any EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *context)  {
    return context -> getText();
}

std::any EvalVisitor::visitFactor(Python3Parser::FactorContext *context)  {
    if (auto *atom_expr = context -> atom_expr()) {
        return visit(atom_expr);
    }
    auto res = visit(context -> factor());
    if (auto *flag = std::any_cast<bool>(&res)) {
        res = int2048(*flag ? 1LL : 0LL);
    }
    if (context -> MINUS()) {
        if (auto *number = std::any_cast<double>(&res)) {
            return -(*number);
        }
        return -std::any_cast<int2048>(res);
    }
    return res;
}

// 这个还要改！
std::any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *context)  {
    if (auto *trailer = context -> trailer()) {
        // 有括号()
        auto *name = context -> atom() -> NAME();
        auto *args = trailer -> arglist();

        if (name -> getText() == "print") {
            if (!args) {
                std::cout << "\n";
                return {};
            }
            std::string res = "";
            int size = (args -> argument()).size();
            for (int i = 0; i < size; i++) {
                auto value = visit(args -> argument(i) -> test(0));
                res += toStr(value);
                if (i < size - 1) res += " ";
            }
            std::cout << res << '\n';
            return {};
        }

        auto it = function.find(name -> getText());
        // 函数分支
        if (it != function.end()) {
            auto *suite = (it -> second).suite;

            // 这里要给参数赋值
            auto &parameters = it -> second.parameters;
            std::unordered_map<std::string, std::any> local;
            for (int i = 0; i < parameters.size(); i++) {
                local[parameters[i]] = visit(args -> argument(i) -> test(0));
            }
            scope.push(local);
            auto res = visit(suite);
            scope.pop();

            if (auto *signal = std::any_cast<FlowSignal>(&res)) {
                if (signal -> kind == FlowKind::Return && signal -> value.has_value()) {
                    return signal -> value;
                }
            }
            return None{};
        }   

        // 类型转换
        else {
            auto temp = visit(args -> argument(0) -> test(0));
            if (name -> getText() == "int") {
                if (temp.type() == typeid(bool)) {
                    if (std::any_cast<bool>(temp)) return int2048(1LL);
                    else return int2048(0LL);
                } 
                if (temp.type() == typeid(double)) {
                    long long num = std::any_cast<double>(temp);
                    return int2048(num);
                }
                if (temp.type() == typeid(std::string)) {
                    return int2048(std::any_cast<std::string>(temp));
                }
            }
            if (name -> getText() == "float") {
                if (temp.type() == typeid(bool)) {
                    if (std::any_cast<bool>(temp)) return 1.0;
                    else return 0.0;
                } 
                if (temp.type() == typeid(int2048)) {
                    return int2048ToDouble(std::any_cast<int2048>(temp));
                }
                if (temp.type() == typeid(std::string)) {
                    return std::stod(std::any_cast<std::string>(temp));
                }
            }
            if (name -> getText() == "str") {
                return toStr(temp);
            }
            if (name -> getText() == "bool") {
                return toBool(temp);
            }
            return {};
        }
    }
    else return visit(context -> atom());
}

std::any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *context)  {
    if (auto *arg = context -> arglist()) {
        return visit(arg);
    }
    return {};
}

// 这个还要改！
std::any EvalVisitor::visitAtom(Python3Parser::AtomContext *context)  {
    if (auto *test = context -> test()) {
        return visit(test);
    }
    if (auto *number = context -> NUMBER()) {
        // return std::stoll(number -> getText());
        std::string text = number -> getText();
        if (text.find('.') != std::string::npos) {
            return std::stod(text);
        }
        return int2048(text);
    }
    if (auto *none = context -> NONE()) {
        return None{};
    }
    if (auto *True = context -> TRUE()) {
        return true;
    }
    if (auto *False = context -> FALSE()) {
        return false;
    }
    if (auto *name = context -> NAME()) {
        auto key = name -> getText();
        if (!scope.empty()) {
            auto &local = scope.top();
            auto it = local.find(key);
            if (it != local.end()) {
                return it -> second;
            }
        }
        return global[key];
    }
    if (context -> STRING().size()) {
        auto String = context -> STRING();
        std::string res = "";
        for (int i = 0; i < String.size(); i++) {
            std::string temp = String[i] -> getText();
            temp = temp.substr(1, temp.size() - 2); // 去掉 ""
            res += temp;
        }
        return res;
    }
    if (auto *fstring = context -> format_string()) {
        
    }
    return {};
}

// std::any EvalVisitor::visitFormat_string(Python3Parser::Format_stringContext *context)  {

// }

std::any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *context)  {
    // testlist: test (',' test)* (',')?; //算式  eg： a,b   a   a+b
    if (context -> COMMA().empty()) {
        return visit(context -> test(0));
    }
    std::vector<std::any> testlist;
    auto tests = context -> test();
    for (int i = 0; i < tests.size(); i++) {
        testlist.push_back(visit(tests[i]));
    }
    return testlist;
}

// std::any EvalVisitor::visitArglist(Python3Parser::ArglistContext *context)  {

// }

// std::any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *context)  {

// }
