#pragma once

#include "Node.h"
#include <memory>
#include <string>

class SymLink : public Node {
public:
    SymLink(const std::string& name,
            const std::string& path,
            const std::string& targetPath,
            std::shared_ptr<Node> target = nullptr);

    ~SymLink() override = default;

    NodeType  getType() const override;
    long long getSize() const override;
    bool      isReadable() const override;
    bool      isWritable() const override;
    bool      isExecutable() const override;

    const std::string&       getTargetPath() const;
    std::shared_ptr<Node>    getTarget() const;
    void                     setTargetPath(const std::string& targetPath);
    void                     setTarget(const std::shared_ptr<Node>& target);
    bool                     isDangling() const;

private:
    std::string      m_targetPath;
    std::weak_ptr<Node> m_target;
};
