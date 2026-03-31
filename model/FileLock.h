#pragma once

#include <string>

enum class LockType {
    SHARED,   // Multiple readers allowed
    EXCLUSIVE // Single writer only
};

class FileLock {
public:
    FileLock(const std::string& targetPath, int ownerUid, LockType type);

    const std::string& getTargetPath() const;
    int getOwnerUid() const;
    LockType getType() const;

    bool canRead(int uid) const;
    bool canWrite(int uid) const;

private:
    std::string m_targetPath;
    int m_ownerUid;
    LockType m_type;
};
