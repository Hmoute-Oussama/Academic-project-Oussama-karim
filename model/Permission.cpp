// ============================================================
// model/Permission.cpp
// ============================================================

#include "Permission.h"
#include <stdexcept>

// ── Constructeurs ─────────────────────────────────────────────
Permission::Permission()
    : m_ownerUid(0)
    , m_ownerGid(0)
{
    fromOctal(0644);  // défaut : rw-r--r--
}

Permission::Permission(int octal)
    : m_ownerUid(0)
    , m_ownerGid(0)
{
    fromOctal(octal);
}

// ── fromOctal (helper privé) ──────────────────────────────────
void Permission::fromOctal(int octal) {
    if (octal < 0 || octal > 0777)
        throw std::invalid_argument("Permission: octal must be between 0 and 0777");

    m_ownerRead    = (octal & 0400) != 0;
    m_ownerWrite   = (octal & 0200) != 0;
    m_ownerExecute = (octal & 0100) != 0;

    m_groupRead    = (octal & 0040) != 0;
    m_groupWrite   = (octal & 0020) != 0;
    m_groupExecute = (octal & 0010) != 0;

    m_otherRead    = (octal & 0004) != 0;
    m_otherWrite   = (octal & 0002) != 0;
    m_otherExecute = (octal & 0001) != 0;
}

// ── Vérifications pour un utilisateur donné ──────────────────
bool Permission::canRead(int uid, int gid) const {
    if (uid == m_ownerUid) return m_ownerRead;
    if (gid == m_ownerGid) return m_groupRead;
    return m_otherRead;
}

bool Permission::canWrite(int uid, int gid) const {
    if (uid == m_ownerUid) return m_ownerWrite;
    if (gid == m_ownerGid) return m_groupWrite;
    return m_otherWrite;
}

bool Permission::canExecute(int uid, int gid) const {
    if (uid == m_ownerUid) return m_ownerExecute;
    if (gid == m_ownerGid) return m_groupExecute;
    return m_otherExecute;
}

// ── Getters bruts ─────────────────────────────────────────────
bool Permission::ownerRead()    const { return m_ownerRead;    }
bool Permission::ownerWrite()   const { return m_ownerWrite;   }
bool Permission::ownerExecute() const { return m_ownerExecute; }

bool Permission::groupRead()    const { return m_groupRead;    }
bool Permission::groupWrite()   const { return m_groupWrite;   }
bool Permission::groupExecute() const { return m_groupExecute; }

bool Permission::otherRead()    const { return m_otherRead;    }
bool Permission::otherWrite()   const { return m_otherWrite;   }
bool Permission::otherExecute() const { return m_otherExecute; }

int Permission::getOctal() const {
    int octal = 0;
    if (m_ownerRead)    octal |= 0400;
    if (m_ownerWrite)   octal |= 0200;
    if (m_ownerExecute) octal |= 0100;
    if (m_groupRead)    octal |= 0040;
    if (m_groupWrite)   octal |= 0020;
    if (m_groupExecute) octal |= 0010;
    if (m_otherRead)    octal |= 0004;
    if (m_otherWrite)   octal |= 0002;
    if (m_otherExecute) octal |= 0001;
    return octal;
}

// ── Setters ───────────────────────────────────────────────────
void Permission::setOwnerRead   (bool v) { m_ownerRead    = v; }
void Permission::setOwnerWrite  (bool v) { m_ownerWrite   = v; }
void Permission::setOwnerExecute(bool v) { m_ownerExecute = v; }

void Permission::setGroupRead   (bool v) { m_groupRead    = v; }
void Permission::setGroupWrite  (bool v) { m_groupWrite   = v; }
void Permission::setGroupExecute(bool v) { m_groupExecute = v; }

void Permission::setOtherRead   (bool v) { m_otherRead    = v; }
void Permission::setOtherWrite  (bool v) { m_otherWrite   = v; }
void Permission::setOtherExecute(bool v) { m_otherExecute = v; }

void Permission::setOctal(int octal) {
    fromOctal(octal);
}

// ── toString ─────────────────────────────────────────────────
std::string Permission::toString() const {
    std::string s = "---------";
    if (m_ownerRead)    s[0] = 'r';
    if (m_ownerWrite)   s[1] = 'w';
    if (m_ownerExecute) s[2] = 'x';
    if (m_groupRead)    s[3] = 'r';
    if (m_groupWrite)   s[4] = 'w';
    if (m_groupExecute) s[5] = 'x';
    if (m_otherRead)    s[6] = 'r';
    if (m_otherWrite)   s[7] = 'w';
    if (m_otherExecute) s[8] = 'x';
    return s;  // ex: "rwxr-xr-x"
}