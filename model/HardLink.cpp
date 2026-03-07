#include "HardLink.h"

#include <ctime>
#include <stdexcept>

HardLink::HardLink(const std::string& name,
                   const std::string& path,
                   const std::shared_ptr<Node>& target)
    : Node(name, path, NodeType::HARDLINK)
    , m_target(target) {
    if (!target) {
        throw std::invalid_argument("HardLink: target cannot be null");
    }
}

NodeType HardLink::getType() const {
    return NodeType::HARDLINK;
}

long long HardLink::getSize() const {
    auto target = m_target.lock();
    return target ? target->getSize() : 0;
}

bool HardLink::isReadable() const {
    auto target = m_target.lock();
    return target ? target->isReadable() : false;
}

bool HardLink::isWritable() const {
    auto target = m_target.lock();
    return target ? target->isWritable() : false;
}

bool HardLink::isExecutable() const {
    auto target = m_target.lock();
    return target ? target->isExecutable() : false;
}

std::shared_ptr<Node> HardLink::getTarget() const {
    return m_target.lock();
}

void HardLink::setTarget(const std::shared_ptr<Node>& target) {
    if (!target) {
        throw std::invalid_argument("HardLink: target cannot be null");
    }
    m_target = target;
    m_modifiedAt = std::time(nullptr);
}

bool HardLink::isBroken() const {
    return m_target.expired();
}
