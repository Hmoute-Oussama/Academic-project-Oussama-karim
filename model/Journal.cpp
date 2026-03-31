#include "Journal.h"

void Journal::log(OperationType op, const std::string& path, const std::string& details) {
    LogEntry entry;
    entry.timestamp = std::time(nullptr);
    entry.op = op;
    entry.path = path;
    entry.details = details;
    m_logs.push_back(entry);
}

const std::vector<LogEntry>& Journal::getLogs() const {
    return m_logs;
}

void Journal::clear() {
    m_logs.clear();
}
