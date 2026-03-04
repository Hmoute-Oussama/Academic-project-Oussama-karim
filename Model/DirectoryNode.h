// ============================================================
// model/DirectoryNode.h
// Nœud dossier — hérite de Node
// C++17 pur, aucune dépendance Qt
// ============================================================

#pragma once

#include "Node.h"
#include "Permission.h"
#include <vector>
#include <memory>
#include <string>

class DirectoryNode : public Node {

public:

    // ── Constructeurs ─────────────────────────────────────────
    DirectoryNode(const std::string& name,
                  const std::string& path);

    // ── Destructeur ───────────────────────────────────────────
    ~DirectoryNode() override = default;

    // ── Méthodes virtuelles pures (obligatoires) ──────────────
    NodeType  getType()      const override;
    long long getSize()      const override;  // somme des enfants
    bool      isReadable()   const override;
    bool      isWritable()   const override;
    bool      isExecutable() const override;

    // ── Gestion des enfants ───────────────────────────────────
    void addChild   (std::shared_ptr<Node> node);
    void removeChild(const std::string& name);

    std::shared_ptr<Node> findChild   (const std::string& name)  const;
    bool                  hasChild    (const std::string& name)  const;
    bool                  isEmpty     ()                         const;
    int                   childCount  ()                         const;

    const std::vector<std::shared_ptr<Node>>& getChildren() const;

    // ── Permissions ───────────────────────────────────────────
    const Permission& getPermission()              const;
    void              setPermission(const Permission& perm);

private:

    std::vector<std::shared_ptr<Node>> m_children;
    Permission                         m_permission;
};