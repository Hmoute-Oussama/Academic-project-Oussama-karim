#include "Group.h"

Group::Group(int gid, const std::string& name)
    : m_gid(gid), m_name(name) {}

int Group::getGid() const {
    return m_gid;
}

const std::string& Group::getName() const {
    return m_name;
}

void Group::addMember(int uid) {
    if (!hasMember(uid)) {
        m_members.push_back(uid);
    }
}

void Group::removeMember(int uid) {
    m_members.erase(std::remove(m_members.begin(), m_members.end(), uid), m_members.end());
}

bool Group::hasMember(int uid) const {
    return std::find(m_members.begin(), m_members.end(), uid) != m_members.end();
}

const std::vector<int>& Group::getMembers() const {
    return m_members;
}
