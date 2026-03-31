#include "Snapshot.h"

Snapshot::Snapshot(const std::string& filePath, const std::string& content, const std::string& versionName)
    : m_filePath(filePath), m_content(content), m_versionName(versionName) {
    m_timestamp = std::time(nullptr);
}

const std::string& Snapshot::getFilePath() const {
    return m_filePath;
}

const std::string& Snapshot::getContent() const {
    return m_content;
}

const std::string& Snapshot::getVersionName() const {
    return m_versionName;
}

std::time_t Snapshot::getTimestamp() const {
    return m_timestamp;
}
