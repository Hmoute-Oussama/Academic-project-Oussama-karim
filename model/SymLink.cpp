#include "SymLink.h"

#include <ctime>
#include <stdexcept>

SymLink::SymLink(const std::string& name,
                 const std::string& path,
                 const std::string& targetPath,
                 std::shared_ptr<Node> target)
    : Node(name, path, NodeType::SYMLINK)
    , m_targetPath(targetPath)
    , m_target(target) {
    if (targetPath.empty()) {
        throw std::invalid_argument("SymLink: targetPath cannot be empty");
    }
}

NodeType SymLink::getType() const {
    return NodeType::SYMLINK;
}

long long SymLink::getSize() const {
    return static_cast<long long>(m_targetPath.size());
}

bool SymLink::isReadable() const {
    auto target = m_target.lock();
    return target ? target->isReadable() : false;
}

bool SymLink::isWritable() const {
    auto target = m_target.lock();
    return target ? target->isWritable() : false;
}

bool SymLink::isExecutable() const {
    auto target = m_target.lock();
    return target ? target->isExecutable() : false;
}

const std::string& SymLink::getTargetPath() const {
    return m_targetPath;
}

std::shared_ptr<Node> SymLink::getTarget() const {
    return m_target.lock();
}

void SymLink::setTargetPath(const std::string& targetPath) {
    if (targetPath.empty()) {
        throw std::invalid_argument("SymLink: targetPath cannot be empty");
    }
    m_targetPath = targetPath;
    m_modifiedAt = std::time(nullptr);
}

void SymLink::setTarget(const std::shared_ptr<Node>& target) {
    m_target = target;
    m_modifiedAt = std::time(nullptr);
}

bool SymLink::isDangling() const {
    return m_target.expired();
}
