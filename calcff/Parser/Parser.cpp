#include "Parser.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cctype>
#include <Windows.h> // MessageBoxA


void Parser::removeWhitespaces(ArithmeticExpr& expr) const
{
    for (auto& e : expr)
        e.erase(std::remove_if(e.begin(), e.end(), std::isspace), e.end());
}

bool Parser::isValidCharacters(const ArithmeticExpr& expressions) const
{
    std::string parentheses;
    for (const auto& expr : expressions) {
        if (expr.find_first_not_of("()+-*/^0123456789") != std::string::npos) {
            const std::string info_msg("Expression: '" + expr
                                       + "'\nContain invalid characters!");
            MessageBoxA(NULL, info_msg.c_str(), "Calcff", MB_ICONINFORMATION);
            return false;
        }
    }
    return true;
}

bool Parser::arePair(char opening, char closing) const
{
    return opening == '(' && closing == ')';
}

bool Parser::areParenthesesBalanced(const ArithmeticExpr& expressions) const
{
    std::stack<char> st;
    for (const auto& expr : expressions) {
        for (const auto& e : expr) {
            if (e == '(') {
                st.push(e);
            } else if (e == ')') {
                if (st.empty() || !arePair(st.top(), e)) {
                    const std::string info_msg("Expression: '" + expr
                                               + "'\nContain extra parentheses!");
                    MessageBoxA(NULL, info_msg.c_str(), "Calcff", MB_ICONINFORMATION);
                    return false;
                } else {
                    st.pop();
                }
            }
        }
    }
    return true;//st.empty();
}

bool Parser::isOperator(const std::string& ch) const
{
    return (ch == "*" || ch == "/" || ch == "+" || ch == "-" || ch == "^");
}

int Parser::getPriority(const std::string& ch) const
{
    if (ch == "^")
        return 3;
    else if (ch == "*" || ch == "/")
        return 2;
    else if (ch == "+" || ch == "-")
        return 1;
    return 0;
}

std::vector<std::string> Parser::getVectorTokens(const std::string& str_tokens) const
{
    std::vector<std::string> vec_tokens;
    vec_tokens.reserve(str_tokens.length());
    std::istringstream iss(str_tokens);
    while (iss) {
        std::string temp;
        iss >> temp;
        vec_tokens.push_back(temp);
    }

    //for (const auto& t : str_tokens)
    //    vec_tokens.push_back(std::string(1, t));
    return vec_tokens;
}

std::string Parser::infixToPostfix(const std::string& expr) const
{
    std::string postfix;
    std::stack<char> st;
    st.push('N');

    for (char ch : expr) {
        // if the scanned digit, add it to 'postfix'
        if (std::isdigit(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            st.push('(');
        } else if (ch == ')') {
            while (st.top() != 'N' && st.top() != '(') {
                char c = st.top();
                st.pop();
                postfix += ' ';
                postfix += c;
            }
            if (st.top() == '(') {
                st.pop();
            }
        } else {  // if an operator is scanned
            while (st.top() != 'N' && getPriority(std::string(1, ch))
                                   <= getPriority(std::string(1, st.top()))) {
                char c = st.top();
                st.pop();
                postfix += ' ';
                postfix += c;
            }
            postfix += ' ';
            st.push(ch);
        }
    }

    // pop all the remaining elements from the stack
    while (st.top() != 'N') {
        char c = st.top();
        st.pop();
        postfix += ' ';
        postfix += c;
    }
    return postfix;
}