#pragma once

#include "DirectoryNode.h"
#include "FileNode.h"
#include "HardLink.h"
#include "SymLink.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class FileSystem {
public:
    FileSystem();

    std::shared_ptr<DirectoryNode> getRoot() const;
    std::string                    getCurrentDirectoryPath() const;
    void                           changeDirectory(const std::string& path);

    std::shared_ptr<DirectoryNode> createDirectory(const std::string& path);
    std::shared_ptr<FileNode>      createFile(const std::string& path, const std::string& content = "");
    std::shared_ptr<SymLink>       createSymLink(const std::string& linkPath, const std::string& targetPath);
    std::shared_ptr<HardLink>      createHardLink(const std::string& linkPath, const std::string& targetPath);

    std::shared_ptr<Node>          getNode(const std::string& path) const;
    bool                           exists(const std::string& path) const;
    void                           remove(const std::string& path);
    std::vector<std::shared_ptr<Node>> list(const std::string& path = ".") const;

private:
    std::shared_ptr<DirectoryNode> m_root;
    std::shared_ptr<DirectoryNode> m_cwd;
    std::unordered_map<std::string, std::shared_ptr<Node>> m_nodes;

    std::string                    normalizePath(const std::string& path) const;
    std::string                    parentPath(const std::string& path) const;
    std::string                    nodeName(const std::string& path) const;
    std::shared_ptr<DirectoryNode> getDirectory(const std::string& path) const;
};
