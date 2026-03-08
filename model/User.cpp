#include "User.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>

User::User()
    : uid_(0), name_("unknown"), password_(""),
      primaryGroupId_(0), isAdmin_(false),
      homeDirectory_("/home/unknown") {}

User::User(int uid, const std::string& name, const std::string& password)
    : uid_(uid), name_(name), password_(password),
      primaryGroupId_(uid), isAdmin_(false),
      homeDirectory_("/home/" + name) {}


int User::getUid() const {
    return uid_;
}

std::string User::getName() const {
    return name_;
}

std::string User::getPassword() const {
    return password_;
}

int User::getPrimaryGroupId() const {
    return primaryGroupId_;
}

std::vector<int> User::getGroupIds() const {
    return groupIds_;
}

std::string User::getHomeDirectory() const {
    return homeDirectory_;
}

bool User::isAdmin() const {
    return isAdmin_;
}


void User::setName(const std::string& name) {
    if (name.empty()) throw std::invalid_argument("Username cannot be empty");
    name_ = name;
}

void User::setPassword(const std::string& password) {
    if (password.empty()) throw std::invalid_argument("Password cannot be empty");
    password_ = password;
}

void User::setPrimaryGroupId(int gid) {
    primaryGroupId_ = gid;
}

void User::setHomeDirectory(const std::string& path) {
    homeDirectory_ = path;
}

void User::setAdmin(bool admin) {
    isAdmin_ = admin;
}


void User::addGroup(int gid) {
    if (!belongsToGroup(gid)) {
        groupIds_.push_back(gid);
    }
}

void User::removeGroup(int gid) {
    groupIds_.erase(
        std::remove(groupIds_.begin(), groupIds_.end(), gid),
        groupIds_.end()
    );
}

bool User::belongsToGroup(int gid) const {
    if (primaryGroupId_ == gid) return true;
    return std::find(groupIds_.begin(), groupIds_.end(), gid) != groupIds_.end();
}


bool User::checkPassword(const std::string& input) const {
    return input == password_;
}

std::string User::toString() const {
    std::ostringstream oss;
    oss << "User{"
        << "uid=" << uid_
        << ", name=" << name_
        << ", home=" << homeDirectory_
        << ", admin=" << (isAdmin_ ? "yes" : "no")
        << ", primaryGroup=" << primaryGroupId_
        << ", groups=[";
    for (size_t i = 0; i < groupIds_.size(); ++i) {
        oss << groupIds_[i];
        if (i + 1 < groupIds_.size()) oss << ",";
    }
    oss << "]}";
    return oss.str();
}