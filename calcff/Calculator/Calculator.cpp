#include "Calculator.h"
#include <iostream>
#include <sstream>

void Calculator::run() const
{
    std::cout << "Enter the filename: ";
    std::string filename;
    std::getline(std::cin, filename);

    File file(filename);
    ArithmeticExpr expr;
    if (!file.extractExpressions(expr)) {
        exit(1);
    }

    parser_.removeWhitespaces(expr);
    if (!parser_.isValidCharacters(expr)) {
        exit(1);
    }

    if (!parser_.areParenthesesBalanced(expr)) {
        exit(1);
    }

    // conver from infix form to postfix
    std::vector<std::string> postfix_expr;
    postfix_expr.reserve(expr.size());
    for (const auto& e : expr)
        postfix_expr.push_back(parser_.infixToPostfix(e));

    // calculate postfix arithmetic expressions
    std::vector<double> answers;
    answers.reserve(postfix_expr.size());
    for (const auto& pe : postfix_expr) {
        auto vec_tokens = parser_.getVectorTokens(pe);
        answers.push_back(calculate(vec_tokens));
    }

    file.writeToFile(answers);
    file.showResults();
}

double Calculator::calculate(const std::vector<std::string>& tokens) const
{
    std::stack<std::string> st;

    for (const auto& ch : tokens) {
        const std::string token = ch;

        if (!parser_.isOperator(token)) {
            st.push(token);
        } else {
            double result{};

            // Token is an operator: pop top two entries
            const std::string val2 = st.top();
            st.pop();
            const double d2 = std::stod(val2);

            if (!st.empty()) {
                const std::string val1 = st.top();
                st.pop();
                const double d1 = std::stod(val1);

                result = token == "+" ? d1 + d2 :
                    token == "-" ? d1 - d2 :
                    token == "*" ? d1 * d2 :
                    token == "/" ? d1 / d2 :
                    std::pow(d1, d2);
            } else {
                result = (token == "-") ? -d2 : d2;
            }

            // Push result onto stack
            std::ostringstream s;
            s << result;
            st.push(s.str());
        }
    }

    st.pop();
    return std::stod(st.top());
}

