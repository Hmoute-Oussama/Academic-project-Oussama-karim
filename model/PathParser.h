//
// Created by Latitude 5550 on 3/8/2026.
//

#pragma once
#include <string>
#include <vector>

class PathParser {
public:

    static std::vector<std::string> parse(const std::string& path);


    static std::string resolve(const std::string& cwd, const std::string& path);


    static std::string normalize(const std::string& path);


    static bool isAbsolute(const std::string& path);


    static std::string parentPath(const std::string& path);


    static std::string baseName(const std::string& path);


    static std::string join(const std::string& base, const std::string& part);


    static std::pair<std::string, std::string> splitPath(const std::string& path);
};