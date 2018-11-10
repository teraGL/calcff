#pragma once

#include <string>
#include <vector>

using ArithmeticExpr = std::vector<std::string>;

class File
{
public:
    File() = delete;
    explicit File(const std::string& filename);
    bool extractExpressions(ArithmeticExpr& expressions) const;
    void writeToFile(const std::vector<double>& answers) const;
    void showResults() const;

private:
    std::string filename_;
    const std::string answer_file_ = "answer.txt";
};