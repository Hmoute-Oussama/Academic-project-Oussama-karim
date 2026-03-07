#include "FileSystem.h"

#include <sstream>
#include <stdexcept>

FileSystem::FileSystem() {
    m_root = std::make_shared<DirectoryNode>("/", "/");
    m_cwd = m_root;
    m_nodes["/"] = m_root;
}

std::shared_ptr<DirectoryNode> FileSystem::getRoot() const {
    return m_root;
}

std::string FileSystem::getCurrentDirectoryPath() const {
    return m_cwd->getPath();
}

void FileSystem::changeDirectory(const std::string& path) {
    auto dir = getDirectory(path);
    if (!dir) {
        throw std::runtime_error("FileSystem: directory not found");
    }
    m_cwd = dir;
}

std::shared_ptr<DirectoryNode> FileSystem::createDirectory(const std::string& path) {
    const std::string normalized = normalizePath(path);
    if (exists(normalized)) {
        throw std::runtime_error("FileSystem: node already exists at '" + normalized + "'");
    }

    auto parent = getDirectory(parentPath(normalized));
    if (!parent) {
        throw std::runtime_error("FileSystem: parent directory not found");
    }

    const std::string name = nodeName(normalized);
    auto dir = std::make_shared<DirectoryNode>(name, normalized);
    parent->addChild(dir);
    m_nodes[normalized] = dir;
    return dir;
}

std::shared_ptr<FileNode> FileSystem::createFile(const std::string& path, const std::string& content) {
    const std::string normalized = normalizePath(path);
    if (exists(normalized)) {
        throw std::runtime_error("FileSystem: node already exists at '" + normalized + "'");
    }

    auto parent = getDirectory(parentPath(normalized));
    if (!parent) {
        throw std::runtime_error("FileSystem: parent directory not found");
    }

    const std::string name = nodeName(normalized);
    auto file = std::make_shared<FileNode>(name, normalized, content);
    parent->addChild(file);
    m_nodes[normalized] = file;
    return file;
}

std::shared_ptr<SymLink> FileSystem::createSymLink(const std::string& linkPath, const std::string& targetPath) {
    const std::string normalizedLink = normalizePath(linkPath);
    if (exists(normalizedLink)) {
        throw std::runtime_error("FileSystem: node already exists at '" + normalizedLink + "'");
    }

    auto parent = getDirectory(parentPath(normalizedLink));
    if (!parent) {
        throw std::runtime_error("FileSystem: parent directory not found");
    }

    const std::string normalizedTarget = normalizePath(targetPath);
    auto targetNode = getNode(normalizedTarget);
    const std::string name = nodeName(normalizedLink);

    auto link = std::make_shared<SymLink>(name, normalizedLink, normalizedTarget, targetNode);
    parent->addChild(link);
    m_nodes[normalizedLink] = link;
    return link;
}

std::shared_ptr<HardLink> FileSystem::createHardLink(const std::string& linkPath, const std::string& targetPath) {
    const std::string normalizedLink = normalizePath(linkPath);
    if (exists(normalizedLink)) {
        throw std::runtime_error("FileSystem: node already exists at '" + normalizedLink + "'");
    }

    auto parent = getDirectory(parentPath(normalizedLink));
    if (!parent) {
        throw std::runtime_error("FileSystem: parent directory not found");
    }

    const std::string normalizedTarget = normalizePath(targetPath);
    auto targetNode = getNode(normalizedTarget);
    if (!targetNode) {
        throw std::runtime_error("FileSystem: hard link target not found");
    }
    if (targetNode->getType() == NodeType::DIRECTORY) {
        throw std::runtime_error("FileSystem: hard link to directory is not allowed");
    }

    const std::string name = nodeName(normalizedLink);
    auto link = std::make_shared<HardLink>(name, normalizedLink, targetNode);
    parent->addChild(link);
    m_nodes[normalizedLink] = link;
    return link;
}

std::shared_ptr<Node> FileSystem::getNode(const std::string& path) const {
    const std::string normalized = normalizePath(path);
    auto it = m_nodes.find(normalized);
    if (it == m_nodes.end()) {
        return nullptr;
    }
    return it->second;
}

bool FileSystem::exists(const std::string& path) const {
    return getNode(path) != nullptr;
}

void FileSystem::remove(const std::string& path) {
    const std::string normalized = normalizePath(path);
    if (normalized == "/") {
        throw std::runtime_error("FileSystem: cannot remove root directory");
    }

    auto node = getNode(normalized);
    if (!node) {
        throw std::runtime_error("FileSystem: node not found at '" + normalized + "'");
    }

    if (node->getType() == NodeType::DIRECTORY) {
        auto dir = std::dynamic_pointer_cast<DirectoryNode>(node);
        if (dir && !dir->isEmpty()) {
            throw std::runtime_error("FileSystem: cannot remove non-empty directory");
        }
    }

    auto parent = getDirectory(parentPath(normalized));
    if (!parent) {
        throw std::runtime_error("FileSystem: parent directory not found");
    }

    parent->removeChild(node->getName());
    m_nodes.erase(normalized);
}

std::vector<std::shared_ptr<Node>> FileSystem::list(const std::string& path) const {
    auto dir = getDirectory(path);
    if (!dir) {
        throw std::runtime_error("FileSystem: directory not found");
    }
    return dir->getChildren();
}

std::string FileSystem::normalizePath(const std::string& path) const {
    if (path.empty()) {
        throw std::invalid_argument("FileSystem: path cannot be empty");
    }

    std::string raw = path;
    if (raw.front() != '/') {
        if (m_cwd->getPath() == "/") {
            raw = "/" + raw;
        } else {
            raw = m_cwd->getPath() + "/" + raw;
        }
    }

    std::vector<std::string> parts;
    std::stringstream ss(raw);
    std::string token;

    while (std::getline(ss, token, '/')) {
        if (token.empty() || token == ".") {
            continue;
        }
        if (token == "..") {
            if (!parts.empty()) {
                parts.pop_back();
            }
            continue;
        }
        parts.push_back(token);
    }

    if (parts.empty()) {
        return "/";
    }

    std::string normalized = "/";
    for (size_t i = 0; i < parts.size(); ++i) {
        normalized += parts[i];
        if (i + 1 < parts.size()) {
            normalized += "/";
        }
    }
    return normalized;
}

std::string FileSystem::parentPath(const std::string& path) const {
    const std::string normalized = normalizePath(path);
    if (normalized == "/") {
        throw std::invalid_argument("FileSystem: root has no parent");
    }

    const size_t slashPos = normalized.find_last_of('/');
    if (slashPos == 0) {
        return "/";
    }
    return normalized.substr(0, slashPos);
}

std::string FileSystem::nodeName(const std::string& path) const {
    const std::string normalized = normalizePath(path);
    if (normalized == "/") {
        return "/";
    }

    const size_t slashPos = normalized.find_last_of('/');
    return normalized.substr(slashPos + 1);
}

std::shared_ptr<DirectoryNode> FileSystem::getDirectory(const std::string& path) const {
    auto node = getNode(path);
    if (!node) {
        return nullptr;
    }
    return std::dynamic_pointer_cast<DirectoryNode>(node);
}
