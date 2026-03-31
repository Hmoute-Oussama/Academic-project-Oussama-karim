#pragma once

#include <unordered_map>

class Quota {
public:
    Quota() = default;

    void setQuota(int uid, long long maxBytes);
    long long getQuota(int uid) const;
    long long getUsed(int uid) const;

    bool hasSpace(int uid, long long size) const;
    bool allocate(int uid, long long size);
    void freeSpace(int uid, long long size);

private:
    std::unordered_map<int, long long> m_userQuotas;
    std::unordered_map<int, long long> m_userUsage;
};
