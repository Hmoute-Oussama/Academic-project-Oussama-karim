#include "Quota.h"

void Quota::setQuota(int uid, long long maxBytes) {
    m_userQuotas[uid] = maxBytes;
}

long long Quota::getQuota(int uid) const {
    auto it = m_userQuotas.find(uid);
    return it != m_userQuotas.end() ? it->second : -1; // -1 represents unlimited or no quota set
}

long long Quota::getUsed(int uid) const {
    auto it = m_userUsage.find(uid);
    return it != m_userUsage.end() ? it->second : 0;
}

bool Quota::hasSpace(int uid, long long size) const {
    long long quota = getQuota(uid);
    if (quota == -1) return true; // No limit
    return (getUsed(uid) + size <= quota);
}

bool Quota::allocate(int uid, long long size) {
    if (!hasSpace(uid, size)) {
        return false;
    }
    m_userUsage[uid] += size;
    return true;
}

void Quota::freeSpace(int uid, long long size) {
    if (m_userUsage[uid] >= size) {
        m_userUsage[uid] -= size;
    } else {
        m_userUsage[uid] = 0;
    }
}
