#include "Node.h"

#include <stdexcept>

Node::Node(const std::string& name, const std::string& path, NodeType type)
    : m_name(name)
    , m_path(path)
    , m_type(type)
    , m_createdAt(std::time(nullptr))
    , m_modifiedAt(m_createdAt)
    , m_accessedAt(m_createdAt)
    , m_ownerUid(0)
    , m_ownerGid(0)
    , m_hidden(!name.empty() && name[0] == '.')
    , m_locked(false) {
    if (name.empty()) {
        throw std::invalid_argument("Node: name cannot be empty");
    }
    if (path.empty()) {
        throw std::invalid_argument("Node: path cannot be empty");
    }
}

NodeType Node::getType() const { return m_type; }

const std::string& Node::getName() const { return m_name; }
const std::string& Node::getPath() const { return m_path; }
std::time_t Node::getCreatedAt() const { return m_createdAt; }
std::time_t Node::getModifiedAt() const { return m_modifiedAt; }
std::time_t Node::getAccessedAt() const { return m_accessedAt; }
int Node::getOwnerUid() const { return m_ownerUid; }
int Node::getOwnerGid() const { return m_ownerGid; }
bool Node::isHidden() const { return m_hidden; }
bool Node::isLocked() const { return m_locked; }

void Node::setName(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Node: name cannot be empty");
    }
    m_name = name;
    m_hidden = (name[0] == '.');
}

void Node::setPath(const std::string& path) {
    if (path.empty()) {
        throw std::invalid_argument("Node: path cannot be empty");
    }
    m_path = path;
}

void Node::setModifiedAt(std::time_t t) { m_modifiedAt = t; }
void Node::setAccessedAt(std::time_t t) { m_accessedAt = t; }

void Node::setOwner(int uid, int gid) {
    m_ownerUid = uid;
    m_ownerGid = gid;
}

void Node::setHidden(bool hidden) { m_hidden = hidden; }
void Node::setLocked(bool locked) { m_locked = locked; }
