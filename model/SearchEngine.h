#pragma once

#include "Node.h"
#include "DirectoryNode.h"
#include <vector>
#include <string>
#include <memory>

class SearchEngine {
public:
    SearchEngine() = default;

    std::vector<std::shared_ptr<Node>> searchByName(std::shared_ptr<DirectoryNode> root, const std::string& query) const;
    std::vector<std::shared_ptr<Node>> searchByExtension(std::shared_ptr<DirectoryNode> root, const std::string& ext) const;

private:
    void searchRecursive(std::shared_ptr<DirectoryNode> current, const std::string& query, std::vector<std::shared_ptr<Node>>& results, bool byExtension) const;
};
