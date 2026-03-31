#pragma once

#include <string>
#include <ctime>

class Snapshot {
public:
    Snapshot(const std::string& filePath, const std::string& content, const std::string& versionName);

    const std::string& getFilePath() const;
    const std::string& getContent() const;
    const std::string& getVersionName() const;
    std::time_t getTimestamp() const;

private:
    std::string m_filePath;
    std::string m_content;
    std::string m_versionName;
    std::time_t m_timestamp;
};
