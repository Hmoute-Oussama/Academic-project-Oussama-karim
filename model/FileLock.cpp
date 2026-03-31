#include "FileLock.h"

FileLock::FileLock(const std::string& targetPath, int ownerUid, LockType type)
    : m_targetPath(targetPath), m_ownerUid(ownerUid), m_type(type) {}

const std::string& FileLock::getTargetPath() const {
    return m_targetPath;
}

int FileLock::getOwnerUid() const {
    return m_ownerUid;
}

LockType FileLock::getType() const {
    return m_type;
}

bool FileLock::canRead(int uid) const {
    if (m_type == LockType::SHARED) return true;
    return m_ownerUid == uid; // Exclusive lock implicitly allows owner to read
}

bool FileLock::canWrite(int uid) const {
    return (m_type == LockType::EXCLUSIVE && m_ownerUid == uid);
}
