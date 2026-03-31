#include "Trash.h"

void Trash::moveToTrash(std::shared_ptr<Node> node) {
    if (node) {
        m_deletedItems[node->getName()] = node;
    }
}

std::shared_ptr<Node> Trash::restore(const std::string& name) {
    auto it = m_deletedItems.find(name);
    if (it != m_deletedItems.end()) {
        std::shared_ptr<Node> restoredNode = it->second;
        m_deletedItems.erase(it);
        return restoredNode;
    }
    return nullptr;
}

void Trash::emptyTrash() {
    m_deletedItems.clear();
}

const std::unordered_map<std::string, std::shared_ptr<Node>>& Trash::getDeletedItems() const {
    return m_deletedItems;
}
