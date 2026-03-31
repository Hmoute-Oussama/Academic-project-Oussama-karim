#pragma once

#include <string>
#include <vector>
#include <algorithm>

class Group {
public:
    Group(int gid, const std::string& name);

    int getGid() const;
    const std::string& getName() const;

    void addMember(int uid);
    void removeMember(int uid);
    bool hasMember(int uid) const;

    const std::vector<int>& getMembers() const;

private:
    int m_gid;
    std::string m_name;
    std::vector<int> m_members;
};
