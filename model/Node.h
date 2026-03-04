// ============================================================
// model/Node.h
// Classe abstraite de base — C++17 pur, aucune dépendance Qt
// ============================================================

#pragma once

#include <string>
#include <ctime>
#include <memory>

// ── Type de nœud ─────────────────────────────────────────────
enum class NodeType {
    REGULAR,      // fichier ordinaire
    DIRECTORY,    // dossier
    SYMLINK,      // lien symbolique
    HARDLINK      // lien physique
};

// ── Forward declarations ──────────────────────────────────────
class Permission;
class User;

// ── Classe abstraite Node ─────────────────────────────────────
class Node {

public:

    // Constructeur
    explicit Node(const std::string& name,
                  const std::string& path,
                  NodeType           type);

    // Destructeur virtuel OBLIGATOIRE
    virtual ~Node() = default;

    // ── Méthodes virtuelles pures ─────────────────────────────
    virtual NodeType  getType()      const = 0;
    virtual long long getSize()      const = 0;
    virtual bool      isReadable()   const = 0;
    virtual bool      isWritable()   const = 0;
    virtual bool      isExecutable() const = 0;

    // ── Getters ───────────────────────────────────────────────
    const std::string& getName()       const;
    const std::string& getPath()       const;
    std::time_t        getCreatedAt()  const;
    std::time_t        getModifiedAt() const;
    std::time_t        getAccessedAt() const;
    int                getOwnerUid()   const;
    int                getOwnerGid()   const;
    bool               isHidden()      const;
    bool               isLocked()      const;

    // ── Setters ───────────────────────────────────────────────
    void setName(const std::string& name);
    void setPath(const std::string& path);
    void setModifiedAt(std::time_t t);
    void setAccessedAt(std::time_t t);
    void setOwner(int uid, int gid);
    void setHidden(bool hidden);
    void setLocked(bool locked);

protected:

    std::string  m_name;
    std::string  m_path;
    NodeType     m_type;

    std::time_t  m_createdAt;
    std::time_t  m_modifiedAt;
    std::time_t  m_accessedAt;

    int          m_ownerUid;
    int          m_ownerGid;

    bool         m_hidden;
    bool         m_locked;

private:

    Node(const Node&)            = delete;
    Node& operator=(const Node&) = delete;
};