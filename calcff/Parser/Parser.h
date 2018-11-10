#pragma once

#include <string>
#include <vector>
#include <stack>

using ArithmeticExpr = std::vector<std::string>;

class Parser
{
public:
    Parser() {};
    void removeWhitespaces(ArithmeticExpr& expr) const;
    std::string infixToPostfix(const std::string& expr) const;

public:
    bool isValidCharacters(const ArithmeticExpr& expressions) const;
    bool arePair(char opening, char closing) const;
    bool areParenthesisBalanced(const ArithmeticExpr& expressions) const;

private:
    bool isOperator(const std::string& ch) const;
    int getPriority(const std::string& ch) const;
};