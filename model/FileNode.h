//
// Created by Latitude 5550 on 3/4/2026.
//

#ifndef UNTITLED5_FILENODE_H
#define UNTITLED5_FILENODE_H


// ============================================================
// model/FileNode.h
// Nœud fichier ordinaire — hérite de Node
// C++17 pur, aucune dépendance Qt
// ============================================================

#pragma once

#include "Node.h"
#include "Permission.h"
#include <string>
#include <vector>

class FileNode : public Node {

public:

    // ── Constructeurs ─────────────────────────────────────────
    FileNode(const std::string& name,
             const std::string& path);

    FileNode(const std::string& name,
             const std::string& path,
             const std::string& content);

    // ── Destructeur ───────────────────────────────────────────
    ~FileNode() override = default;

    // ── Méthodes virtuelles pures (obligatoires) ──────────────
    NodeType  getType()       const override;
    long long getSize()       const override;
    bool      isReadable()    const override;
    bool      isWritable()    const override;
    bool      isExecutable()  const override;

    // ── Contenu du fichier ────────────────────────────────────
    const std::string& getContent()                    const;
    void               setContent(const std::string& content);
    void               appendContent(const std::string& data);
    void               clearContent();

    // ── Extension ─────────────────────────────────────────────
    std::string getExtension() const;   // ex: "pdf", "cpp", "txt"

    // ── Permissions ───────────────────────────────────────────
    const Permission& getPermission()                  const;
    void              setPermission(const Permission& perm);

    // ── MIME type (basé sur extension) ────────────────────────
    std::string getMimeType() const;  // ex: "text/plain", "application/pdf"

private:

    std::string  m_content;     // Contenu textuel du fichier
    Permission   m_permission;  // Permissions rwx

    // ── Helpers privés ────────────────────────────────────────
    std::string extractExtension() const;
};
#endif //UNTITLED5_FILENODE_H