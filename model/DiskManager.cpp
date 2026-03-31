#include "DiskManager.h"

DiskManager::DiskManager(long long totalCapacity)
    : m_totalCapacity(totalCapacity), m_usedSpace(0) {}

long long DiskManager::getTotalCapacity() const {
    return m_totalCapacity;
}

long long DiskManager::getUsedSpace() const {
    return m_usedSpace;
}

long long DiskManager::getFreeSpace() const {
    return m_totalCapacity - m_usedSpace;
}

bool DiskManager::allocate(long long size) {
    if (m_usedSpace + size > m_totalCapacity) {
        return false;
    }
    m_usedSpace += size;
    return true;
}

void DiskManager::freeSpace(long long size) {
    if (m_usedSpace >= size) {
        m_usedSpace -= size;
    } else {
        m_usedSpace = 0;
    }
}
