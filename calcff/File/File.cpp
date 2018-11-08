#include "File.h"
#include <fstream>
#include <iostream>

#include <algorithm>
#include <utility> // std:move()
#include <cctype>

#include <Windows.h>

File::File(const std::string& filename)
    : filename_(filename)
{
}

static inline bool isBlankLine(const std::string& line)
{
    return std::all_of(line.cbegin(), line.cend(), std::isspace);
}

bool File::extractExpressions(std::vector<std::string>& expressions) const
{
    std::ifstream inFile(filename_);
    if (!inFile) {
        std::string error_msg{"Unable to open '" + filename_ + "': File not found"};
        MessageBoxA(NULL, error_msg.c_str(), "Calff", MB_ICONERROR);
        return false;
    }

    // exclude empty lines and lines consist of blank symbols
    std::string line;
    while (std::getline(inFile, line)) {
        if (!isBlankLine(line))
            expressions.push_back(std::move(line));
    }

    if (expressions.empty())
        MessageBoxA(NULL, "File has no arithmetic expressions", "Calff", MB_ICONINFORMATION);

    inFile.close();
    return true;
}