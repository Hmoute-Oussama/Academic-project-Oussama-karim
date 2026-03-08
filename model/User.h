#pragma once
#include <string>
#include <vector>

class Group;

class User {
public:

    User();
    User(int uid, const std::string& name, const std::string& password);


    int getUid() const;
    std::string getName() const;
    std::string getPassword() const;
    int getPrimaryGroupId() const;
    std::vector<int> getGroupIds() const;
    std::string getHomeDirectory() const;
    bool isAdmin() const;


    void setName(const std::string& name);
    void setPassword(const std::string& password);
    void setPrimaryGroupId(int gid);
    void setHomeDirectory(const std::string& path);
    void setAdmin(bool admin);


    void addGroup(int gid);
    void removeGroup(int gid);
    bool belongsToGroup(int gid) const;


    bool checkPassword(const std::string& input) const;
    std::string toString() const;

private:
    int uid_;
    std::string name_;
    std::string password_;      // n9dro n hashiw l password mn b3d b sha-256
    int primaryGroupId_;
    std::vector<int> groupIds_;
    std::string homeDirectory_;
    bool isAdmin_;
};