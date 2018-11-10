#pragma once

#include "../File/File.h"
#include "../Parser/Parser.h"


class Calculator
{
public:
    void run() const;
    double calculate(const std::vector<std::string>& tokens) const;

private:
    Parser parser_;
};