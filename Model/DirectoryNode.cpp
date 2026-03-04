// ============================================================
// model/DirectoryNode.cpp
// ============================================================

#include "DirectoryNode.h"
#include <algorithm>
#include <stdexcept>

// ── Constructeur ──────────────────────────────────────────────
DirectoryNode::DirectoryNode(const std::string& name,
                             const std::string& path)
    : Node(name, path, NodeType::DIRECTORY)
    , m_permission(0755)   // rwxr-xr-x par défaut pour un dossier
{
}

// ── Méthodes virtuelles pures ─────────────────────────────────
NodeType DirectoryNode::getType() const {
    return NodeType::DIRECTORY;
}

long long DirectoryNode::getSize() const {
    long long total = 0;
    for (const auto& child : m_children)
        total += child->getSize();
    return total;
}

bool DirectoryNode::isReadable() const {
    return m_permission.ownerRead();
}

bool DirectoryNode::isWritable() const {
    return m_permission.ownerWrite();
}

bool DirectoryNode::isExecutable() const {
    return m_permission.ownerExecute();
}

// ── Gestion des enfants ───────────────────────────────────────
void DirectoryNode::addChild(std::shared_ptr<Node> node) {
    if (!node)
        throw std::invalid_argument("DirectoryNode: cannot add null child");

    if (hasChild(node->getName()))
        throw std::runtime_error("DirectoryNode: child '" + node->getName() + "' already exists");

    m_children.push_back(node);
    m_modifiedAt = std::time(nullptr);
}

void DirectoryNode::removeChild(const std::string& name) {
    auto it = std::find_if(m_children.begin(), m_children.end(),
        [&name](const std::shared_ptr<Node>& n) {
            return n->getName() == name;
        });

    if (it == m_children.end())
        throw std::runtime_error("DirectoryNode: child '" + name + "' not found");

    m_children.erase(it);
    m_modifiedAt = std::time(nullptr);
}

std::shared_ptr<Node> DirectoryNode::findChild(const std::string& name) const {
    for (const auto& child : m_children)
        if (child->getName() == name)
            return child;
    return nullptr;
}

bool DirectoryNode::hasChild(const std::string& name) const {
    return findChild(name) != nullptr;
}

bool DirectoryNode::isEmpty() const {
    return m_children.empty();
}

int DirectoryNode::childCount() const {
    return static_cast<int>(m_children.size());
}

const std::vector<std::shared_ptr<Node>>& DirectoryNode::getChildren() const {
    return m_children;
}

// ── Permissions ───────────────────────────────────────────────
const Permission& DirectoryNode::getPermission() const {
    return m_permission;
}

void DirectoryNode::setPermission(const Permission& perm) {
    m_permission = perm;
}