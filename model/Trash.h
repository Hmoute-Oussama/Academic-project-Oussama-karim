#pragma once

#include "Node.h"
#include <unordered_map>
#include <memory>
#include <string>

class Trash {
public:
    Trash() = default;

    void moveToTrash(std::shared_ptr<Node> node);
    std::shared_ptr<Node> restore(const std::string& name);
    void emptyTrash();
    const std::unordered_map<std::string, std::shared_ptr<Node>>& getDeletedItems() const;

private:
    std::unordered_map<std::string, std::shared_ptr<Node>> m_deletedItems;
};
