#include "Evalvisitor.h"
#include "int2048.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <vector>
#include <utility>
#ifdef __linux__
#include <sys/resource.h>
#endif


using sjtu::int2048;
struct None {}; 

// 深递归（题目保证栈深度不超过 2000 层）会耗尽默认 8MB 栈空间，
// 在程序启动时尽量调大栈上限，避免合法的深递归测试点出现 RE。
namespace {
struct StackLimitRaiser {
    StackLimitRaiser() {
#ifdef __linux__
        rlimit limit;
        if (getrlimit(RLIMIT_STACK, &limit) == 0) {
            rlim_t wanted = 256ull * 1024 * 1024;
            if (limit.rlim_cur != RLIM_INFINITY && limit.rlim_cur < wanted) {
                limit.rlim_cur = (limit.rlim_max == RLIM_INFINITY || limit.rlim_max > wanted)
                                     ? wanted : limit.rlim_max;
                setrlimit(RLIMIT_STACK, &limit);
            }
        }
#endif
    }
} stackLimitRaiser;
}

static double int2048ToDouble(const sjtu::int2048& value) {
    std::ostringstream text;
    text << value;
    std::string s = text.str();
    // 用 strtod 而不是 stod：超出 double 范围时返回 ±inf 而不是抛 out_of_range
    return std::strtod(s.c_str(), nullptr);
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
            // 与标准 Python 的浮点向下取整除法保持一致：
            // 先修正 fmod 的余数，再对商向下取整（否则 1.0 // 0.1 会错误地得到 10.0）
            double mod = std::fmod(x, y);
            double div = (x - mod) / y;
            if (mod != 0.0) {
                if ((y < 0.0) != (mod < 0.0)) {
                    mod += y;
                    div -= 1.0;
                }
            }
            double floordiv;
            if (div != 0.0) {
                floordiv = std::floor(div);
                if (div - floordiv > 0.5) floordiv += 1.0;
            }
            else {
                floordiv = std::copysign(0.0, x / y);
            }
            return floordiv;
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
    return {}; 
}

std::any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *context) {
    // funcdef: 'def' NAME parameters ':' suite;
    std::string name = context -> NAME() -> getText();
    // 重新定义同名函数时必须整体替换（包括清空旧的参数表与默认值）
    Function fn;
    fn.suite = context -> suite();

    // 参数表
    if (auto *args = context -> parameters() -> typedargslist()) {
        auto test = args -> test();
        auto tfpdef = args -> tfpdef();
        for (auto *param : tfpdef) {
            fn.parameters.push_back(param -> NAME() -> getText());
        }
        for (size_t i = 0; i < test.size(); i++) {
            fn.defaults[fn.parameters[i + tfpdef.size() - test.size()]] = visit(test[i]);
        }
    }
    function[name] = fn;
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

std::any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *context)  {
    if (auto *trailer = context -> trailer()) {
        // 有括号()
        auto *atom = context -> atom();
        std::string name;
        if (auto *identifier = atom -> NAME()) {
            name = identifier -> getText();
        }
        else {
            // 允许 (f)(1) 这种被括号包裹的被调用者
            std::string text = atom -> getText();
            size_t begin = 0, end = text.size();
            while (begin < end && (text[begin] == '(' ||
                   std::isspace(static_cast<unsigned char>(text[begin])))) begin++;
            while (end > begin && (text[end - 1] == ')' ||
                   std::isspace(static_cast<unsigned char>(text[end - 1])))) end--;
            name = text.substr(begin, end - begin);
        }
        auto *args = trailer -> arglist();

        if (name == "print") {
            if (!args) {
                std::cout << "\n";
                return None{};
            }
            std::string res = "";
            int size = (args -> argument()).size();
            for (int i = 0; i < size; i++) {
                auto value = visit(args -> argument(i) -> test(0));
                res += toStr(value);
                if (i < size - 1) res += " ";
            }
            std::cout << res << '\n';
            return None{};
        }

        auto it = function.find(name);
        // 函数分支
        if (it != function.end()) {
            auto *suite = (it -> second).suite;

            // 这里要给参数赋值
            auto &parameters = it -> second.parameters;
            auto &defaults = it -> second.defaults;
            std::unordered_map<std::string, std::any> local;

            // 有参数
            int argument_size = (args == nullptr) ? 0 : args -> argument().size();
            for (int i = 0; i < argument_size; i++) {
                auto *argument = args -> argument(i);
                if (argument -> ASSIGN()) { // 形参
                    auto param_name = argument -> test(0) -> getText();
                    local[param_name] = visit(argument -> test(1));
                }
                else { // 实参
                    local[parameters[i]] = visit(argument -> test(0));
                }
            }
            for (auto param_name : parameters) {
                if (local.find(param_name) == local.end()) {
                    auto default_it = defaults.find(param_name);
                    if (default_it != defaults.end()) {
                        local[param_name] = default_it -> second;
                    }
                    else {
                        local[param_name] = None{};
                    }
                }
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
            if (args == nullptr || args -> argument().empty()) return {};
            auto temp = visit(args -> argument(0) -> test(0));
            if (name == "int") {
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
                if (temp.type() == typeid(int2048)) {
                    return temp;
                }
            }
            if (name == "float") {
                if (temp.type() == typeid(bool)) {
                    if (std::any_cast<bool>(temp)) return 1.0;
                    else return 0.0;
                } 
                if (temp.type() == typeid(int2048)) {
                    return int2048ToDouble(std::any_cast<int2048>(temp));
                }
                if (temp.type() == typeid(std::string)) {
                    std::string text = std::any_cast<std::string>(temp);
                    return std::strtod(text.c_str(), nullptr);
                }
                if (temp.type() == typeid(double)) {
                    return temp;
                }
            }
            if (name == "str") {
                return toStr(temp);
            }
            if (name == "bool") {
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

std::string decodeString(std::string temp, bool is_fstring) {
    std::string res = "";
    res.reserve(temp.size());
    for (size_t j = 0; j < temp.size(); j++) {
        char cur = temp[j];
        if (cur == '\\') {
            // 反斜杠转义：规则参考 C++ 字符串字面量
            if (j + 1 >= temp.size()) {
                res += '\\';
                break;
            }
            char esc = temp[++j];
            switch (esc) {
                case 'a': res += '\a'; break;
                case 'b': res += '\b'; break;
                case 'f': res += '\f'; break;
                case 'n': res += '\n'; break;
                case 'r': res += '\r'; break;
                case 't': res += '\t'; break;
                case 'v': res += '\v'; break;
                case '\\': res += '\\'; break;
                case '\'': res += '\''; break;
                case '"': res += '"'; break;
                case '?': res += '?'; break;
                case '\n': break;  // 续行：反斜杠 + 换行，直接忽略
                case 'x': {
                    // 十六进制转义，最多两位（与 Python 行为一致，保证可显示字符）
                    int value = 0, cnt = 0;
                    while (cnt < 2 && j + 1 < temp.size() &&
                           std::isxdigit(static_cast<unsigned char>(temp[j + 1]))) {
                        char h = temp[++j];
                        if (h >= '0' && h <= '9') value = value * 16 + (h - '0');
                        else if (h >= 'a' && h <= 'f') value = value * 16 + (h - 'a' + 10);
                        else value = value * 16 + (h - 'A' + 10);
                        cnt++;
                    }
                    if (cnt == 0) res += 'x';
                    else res += static_cast<char>(value);
                    break;
                }
                default:
                    if (esc >= '0' && esc <= '7') {
                        // 八进制转义，最多三位
                        int value = esc - '0', cnt = 1;
                        while (cnt < 3 && j + 1 < temp.size() &&
                               temp[j + 1] >= '0' && temp[j + 1] <= '7') {
                            value = value * 8 + (temp[++j] - '0');
                            cnt++;
                        }
                        res += static_cast<char>(value);
                    }
                    else {
                        // 未知转义：保留字符本身（C++ 中为未定义，输入保证合法）
                        res += esc;
                    }
                    break;
            }
        }
        else if (is_fstring && (cur == '{' || cur == '}')) {
            // f-string 中 {{ 与 }} 表示字面大括号
            if (j + 1 < temp.size() && temp[j + 1] == cur) j++;
            res += cur;
        }
        else {
            res += cur;
        }
    }
    return res;
}

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
        std::string Str = "";
        for (int i = 0; i < String.size(); i++) {
            std::string temp = String[i] -> getText();
            temp = temp.substr(1, temp.size() - 2);
            Str += decodeString(temp, 0);
            // 还要处理\t和\\和\\t
        }
        return Str;
    }
    if (auto *fstring = context -> format_string()) {
        return visit(fstring);
    }
    return {};
}

std::any EvalVisitor::visitFormat_string(Python3Parser::Format_stringContext *context)  {
    // format_string: FORMAT_QUOTATION (FORMAT_STRING_LITERAL | '{' testlist '}')* QUOTATION;
    std::string res = "";
    for (auto *child : context -> children) {
        // 表达式
        if (auto *testlist = dynamic_cast<Python3Parser::TestlistContext*>(child)) {
            res += toStr(visit(testlist));
        }
        // 文字 
        else if (auto *terminal = dynamic_cast<antlr4::tree::TerminalNode*>(child)) {
            if (terminal -> getSymbol() -> getType() == Python3Parser::FORMAT_STRING_LITERAL) {
                res += decodeString(terminal -> getText(), 1);
            }
        }
    }
    return res;
}

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
