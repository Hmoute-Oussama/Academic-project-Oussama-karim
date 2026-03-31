#pragma once

#include <string>
#include <vector>
#include <ctime>

enum class OperationType {
    CREATE,
    DELETE,
    MODIFY,
    MOVE,
    CHMOD,
    CHOWN
};

struct LogEntry {
    std::time_t timestamp;
    OperationType op;
    std::string path;
    std::string details;
};

class Journal {
public:
    Journal() = default;

    void log(OperationType op, const std::string& path, const std::string& details = "");
    const std::vector<LogEntry>& getLogs() const;
    void clear();

private:
    std::vector<LogEntry> m_logs;
};
