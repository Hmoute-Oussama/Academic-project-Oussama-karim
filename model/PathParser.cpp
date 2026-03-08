#include "PathParser.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

std::vector<std::string> PathParser::parse(const std::string& path) {
    std::vector<std::string> tokens;
    std::stringstream ss(path);
    std::string token;

    while (std::getline(ss, token, '/')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}
std::string PathParser::normalize(const std::string& path) {
    std::vector<std::string> parts;
    bool absolute = isAbsolute(path);
    std::vector<std::string> tokens = parse(path);

    for (const std::string& token : tokens) {
        if (token == ".") {
        } else if (token == "..") {

            if (!parts.empty()) {
                parts.pop_back();
            } else if (!absolute) {
                parts.push_back("..");
            }

        } else {
            parts.push_back(token);
        }
    }

    std::string result = absolute ? "/" : "";
    for (size_t i = 0; i < parts.size(); ++i) {
        result += parts[i];
        if (i + 1 < parts.size()) result += "/";
    }

    if (result.empty()) result = ".";
    return result;
}
std::string PathParser::resolve(const std::string& cwd, const std::string& path) {
    if (isAbsolute(path)) {
        return normalize(path);
    }
    std::string combined = cwd + "/" + path;
    return normalize(combined);
}

bool PathParser::isAbsolute(const std::string& path) {
    return !path.empty() && path[0] == '/';
}
std::string PathParser::parentPath(const std::string& path) {
    std::string norm = normalize(path);
    if (norm == "/") return "/";

    size_t pos = norm.rfind('/');
    if (pos == std::string::npos) return ".";
    if (pos == 0) return "/";

    return norm.substr(0, pos);
}


std::string PathParser::baseName(const std::string& path) {
    std::string norm = normalize(path);

    if (norm == "/") return "/";

    size_t pos = norm.rfind('/');
    if (pos == std::string::npos) return norm;

    return norm.substr(pos + 1);
}


std::string PathParser::join(const std::string& base, const std::string& part) {
    if (base.empty()) return part;
    if (part.empty()) return base;

    std::string result = base;
    if (result.back() != '/') result += '/';
    if (part.front() == '/') {
        result += part.substr(1);
    } else {
        result += part;
    }
    return normalize(result);
}


std::pair<std::string, std::string> PathParser::splitPath(const std::string& path) {
    return { parentPath(path), baseName(path) };
}