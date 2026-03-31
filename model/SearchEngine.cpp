#include "SearchEngine.h"
#include "FileNode.h"
#include <algorithm>

std::vector<std::shared_ptr<Node>> SearchEngine::searchByName(std::shared_ptr<DirectoryNode> root, const std::string& query) const {
    std::vector<std::shared_ptr<Node>> results;
    if (root) searchRecursive(root, query, results, false);
    return results;
}

std::vector<std::shared_ptr<Node>> SearchEngine::searchByExtension(std::shared_ptr<DirectoryNode> root, const std::string& ext) const {
    std::vector<std::shared_ptr<Node>> results;
    if (root) searchRecursive(root, ext, results, true);
    return results;
}

void SearchEngine::searchRecursive(std::shared_ptr<DirectoryNode> current, const std::string& query, std::vector<std::shared_ptr<Node>>& results, bool byExtension) const {
    for (const auto& child : current->getChildren()) {
        if (byExtension && child->getType() == NodeType::REGULAR) {
            auto fileNode = std::dynamic_pointer_cast<FileNode>(child);
            if (fileNode && fileNode->getExtension() == query) {
                results.push_back(child);
            }
        } else if (!byExtension) {
            if (child->getName().find(query) != std::string::npos) {
                results.push_back(child);
            }
        }
        
        if (child->getType() == NodeType::DIRECTORY) {
            searchRecursive(std::dynamic_pointer_cast<DirectoryNode>(child), query, results, byExtension);
        }
    }
}
