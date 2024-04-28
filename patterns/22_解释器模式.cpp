#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <regex>
/**
 * 基本概念
解释器模式（Interpreter Pattern）是一种行为型设计模式，它定义了一个语言的文法，并且建立一个【解释器】来解释该语言中的句子。

比如说SQL语法、正则表达式，这些内容比较简短，但是表达的内容可不仅仅是字面上的那些符号，计算机想要理解这些语法，就需要解释这个语法规则，
因此解释器模式常用于实现编程语言解释器、正则表达式处理等场景。

组成结构
解释器模式主要包含以下几个角色：

抽象表达式（Abstract Expression）： 定义了解释器的接口，包含了解释器的方法 interpret。
终结符表达式（Terminal Expression）： 在语法中不能再分解为更小单元的符号。
非终结符表达式（Non-terminal Expression）： 文法中的复杂表达式，它由终结符和其他非终结符组成。
上下文（Context）： 包含解释器之外的一些全局信息，可以存储解释器中间结果，也可以用于向解释器传递信息。
举例来说，表达式 "3 + 5 * 2"，数字 "3" 和 "5"， "2" 是终结符，而运算符 "+", "*"都需要两个操作数, 属于非终结符。
*/

class Expression {
public:
    virtual int interpret() = 0;
    virtual ~Expression() {}
};

// 终结符表达式类 - 数字
class NumberExpression : public Expression {
private:
    int value;

public:
    NumberExpression(int val) : value(val) {}

    int interpret() override {
        return value;
    }
};

// 非终结符表达式类 - 加法操作
class AddExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    AddExpression(Expression* l, Expression* r) : left(l), right(r) {}

    int interpret() override {
        return left->interpret() + right->interpret();
    }
};

// 非终结符表达式类 - 乘法操作
class MultiplyExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    MultiplyExpression(Expression* l, Expression* r) : left(l), right(r) {}

    int interpret() override {
        return left->interpret() * right->interpret();
    }
};

// 非终结符表达式类 - 操作符
class OperatorExpression : public Expression {
private:
    std::string oper;

public:
    OperatorExpression(const std::string& op) : oper(op) {}

    int interpret() override {
        throw std::runtime_error("OperatorExpression does not support interpretation");
    }

    std::string getOperator() const {
        return oper;
    }
};

// 解析表达式字符串
int parseExpression(const std::string& expressionStr) {
    std::istringstream iss(expressionStr);
    std::vector<std::string> elements(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    std::stack<Expression*> stack;

    for (const auto& element : elements) {
        if (std::regex_match(element, std::regex("\\d+"))) {
            stack.push(new NumberExpression(std::stoi(element)));
        } else if (element == "+" || element == "*") {
            stack.push(new OperatorExpression(element));
        } else {
            throw std::invalid_argument("Invalid element in expression: " + element);
        }
    }

    while (stack.size() > 1) {
        Expression* right = stack.top();
        stack.pop();
        Expression* operatorExp = stack.top();
        stack.pop();
        Expression* left = stack.top();
        stack.pop();

        if (auto* opExp = dynamic_cast<OperatorExpression*>(operatorExp)) {
            std::string op = opExp->getOperator();
            if (op == "+") {
                stack.push(new AddExpression(left, right));
            } else if (op == "*") {
                stack.push(new MultiplyExpression(left, right));
            }
        } else {
            throw std::invalid_argument("Invalid operator type in expression");
        }
    }

    int result = stack.top()->interpret();
    delete stack.top(); 
    return result;
}

int main() {
    std::vector<std::string> input_lines;
    std::string line;

    while (std::getline(std::cin, line) && !line.empty()) {
        input_lines.push_back(line);
    }

    for (size_t i = 0; i < input_lines.size(); ++i) {
        try {
            int result = parseExpression(input_lines[i]);
            std::cout << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error - " << e.what() << std::endl;
        }
    }

    return 0;
}