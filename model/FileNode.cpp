// ============================================================
// model/FileNode.cpp
// ============================================================

#include "FileNode.h"
#include <algorithm>
#include <stdexcept>

// ── Constructeurs ─────────────────────────────────────────────
FileNode::FileNode(const std::string& name,
                   const std::string& path)
    : Node(name, path, NodeType::REGULAR)
    , m_content("")
    , m_permission(0644)
{
}

FileNode::FileNode(const std::string& name,
                   const std::string& path,
                   const std::string& content)
    : Node(name, path, NodeType::REGULAR)
    , m_content(content)
    , m_permission(0644)
{
}

// ── Méthodes virtuelles pures ─────────────────────────────────
NodeType FileNode::getType() const {
    return NodeType::REGULAR;
}

long long FileNode::getSize() const {
    return static_cast<long long>(m_content.size());
}

bool FileNode::isReadable() const {
    return m_permission.ownerRead();
}

bool FileNode::isWritable() const {
    return m_permission.ownerWrite();
}

bool FileNode::isExecutable() const {
    return m_permission.ownerExecute();
}

// ── Contenu ───────────────────────────────────────────────────
const std::string& FileNode::getContent() const {
    return m_content;
}

void FileNode::setContent(const std::string& content) {
    m_content    = content;
    m_modifiedAt = std::time(nullptr);
}

void FileNode::appendContent(const std::string& data) {
    m_content   += data;
    m_modifiedAt = std::time(nullptr);
}

void FileNode::clearContent() {
    m_content    = "";
    m_modifiedAt = std::time(nullptr);
}

// ── Extension ─────────────────────────────────────────────────
std::string FileNode::getExtension() const {
    return extractExtension();
}

std::string FileNode::extractExtension() const {
    size_t dot = m_name.rfind('.');
    if (dot == std::string::npos || dot == 0)
        return "";
    std::string ext = m_name.substr(dot + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext;
}

// ── Permissions ───────────────────────────────────────────────
const Permission& FileNode::getPermission() const {
    return m_permission;
}

void FileNode::setPermission(const Permission& perm) {
    m_permission = perm;
}

// ── MIME type ─────────────────────────────────────────────────
std::string FileNode::getMimeType() const {
    std::string ext = extractExtension();

    if (ext == "txt")                       return "text/plain";
    if (ext == "html" || ext == "htm")      return "text/html";
    if (ext == "css")                       return "text/css";
    if (ext == "csv")                       return "text/csv";

    if (ext == "cpp" || ext == "h"
     || ext == "c"   || ext == "hpp")       return "text/x-c++src";

    if (ext == "json")                      return "application/json";
    if (ext == "xml")                       return "application/xml";
    if (ext == "pdf")                       return "application/pdf";
    if (ext == "zip")                       return "application/zip";

    if (ext == "png")                       return "image/png";
    if (ext == "jpg" || ext == "jpeg")      return "image/jpeg";
    if (ext == "gif")                       return "image/gif";
    if (ext == "svg")                       return "image/svg+xml";

    if (ext == "mp3")                       return "audio/mpeg";
    if (ext == "wav")                       return "audio/wav";

    if (ext == "mp4")                       return "video/mp4";
    if (ext == "avi")                       return "video/x-msvideo";

    return "application/octet-stream";
}