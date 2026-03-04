//
// Created by Latitude 5550 on 3/4/2026.
//

#ifndef UNTITLED5_PERMISSION_H
#define UNTITLED5_PERMISSION_H

// ============================================================
// model/Permission.h
// Modèle de permissions Unix (rwx) — C++17 pur, aucun Qt
// ============================================================

#pragma once

#include <string>

// ── Bits de permission (style Unix) ──────────────────────────
// owner : rwx = bits 8,7,6
// group : rwx = bits 5,4,3
// other : rwx = bits 2,1,0
// Exemple : 0755 = rwxr-xr-x

class Permission {

public:

    // ── Constructeurs ─────────────────────────────────────────
    Permission();                        // défaut : 0644 (rw-r--r--)
    explicit Permission(int octal);      // ex: Permission(0755)

    // ── Vérifications pour un utilisateur donné ───────────────
    bool canRead   (int uid, int gid) const;
    bool canWrite  (int uid, int gid) const;
    bool canExecute(int uid, int gid) const;

    // ── Getters bruts ─────────────────────────────────────────
    bool ownerRead()    const;
    bool ownerWrite()   const;
    bool ownerExecute() const;

    bool groupRead()    const;
    bool groupWrite()   const;
    bool groupExecute() const;

    bool otherRead()    const;
    bool otherWrite()   const;
    bool otherExecute() const;

    int  getOctal()     const;   // retourne ex: 0755

    // ── Setters ───────────────────────────────────────────────
    void setOwnerRead   (bool v);
    void setOwnerWrite  (bool v);
    void setOwnerExecute(bool v);

    void setGroupRead   (bool v);
    void setGroupWrite  (bool v);
    void setGroupExecute(bool v);

    void setOtherRead   (bool v);
    void setOtherWrite  (bool v);
    void setOtherExecute(bool v);

    void setOctal(int octal);    // ex: setOctal(0755)

    // ── Utilitaires ───────────────────────────────────────────
    std::string toString() const;  // retourne ex: "rwxr-xr-x"

private:

    // ── Attributs ─────────────────────────────────────────────
    bool m_ownerRead;
    bool m_ownerWrite;
    bool m_ownerExecute;

    bool m_groupRead;
    bool m_groupWrite;
    bool m_groupExecute;

    bool m_otherRead;
    bool m_otherWrite;
    bool m_otherExecute;

    // UID/GID du propriétaire du nœud (copié depuis Node)
    int m_ownerUid;
    int m_ownerGid;

    // ── Helpers privés ────────────────────────────────────────
    void fromOctal(int octal);
};

#endif //UNTITLED5_PERMISSION_H