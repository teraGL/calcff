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
    std::vector<std::string> getVectorTokens(const std::string& tokens) const;
    std::string infixToPostfix(const std::string& expr) const;

public:
    bool hasValidCharacters(const ArithmeticExpr& expressions) const;
    bool arePair(char opening, char closing) const;
    bool areParenthesesBalanced(const ArithmeticExpr& expressions) const;

    bool isOperator(const std::string& ch) const;
    int getPriority(const std::string& ch) const;
};