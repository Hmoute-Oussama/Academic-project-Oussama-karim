#pragma once

class DiskManager {
public:
    DiskManager(long long totalCapacity);

    long long getTotalCapacity() const;
    long long getUsedSpace() const;
    long long getFreeSpace() const;

    bool allocate(long long size);
    void freeSpace(long long size);

private:
    long long m_totalCapacity;
    long long m_usedSpace;
};
