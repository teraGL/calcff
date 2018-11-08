#pragma once

#include <string>
#include <vector>

class File
{
public:
    File() = delete;
    explicit File(const std::string& filename);
    bool extractExpressions(std::vector<std::string>& expressions) const;

private:
    std::string filename_;
};