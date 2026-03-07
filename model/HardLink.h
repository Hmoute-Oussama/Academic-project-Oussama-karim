#pragma once

#include "Node.h"
#include <memory>
#include <string>

class HardLink : public Node {
public:
    HardLink(const std::string& name,
             const std::string& path,
             const std::shared_ptr<Node>& target);

    ~HardLink() override = default;

    NodeType  getType() const override;
    long long getSize() const override;
    bool      isReadable() const override;
    bool      isWritable() const override;
    bool      isExecutable() const override;

    std::shared_ptr<Node> getTarget() const;
    void                  setTarget(const std::shared_ptr<Node>& target);
    bool                  isBroken() const;

private:
    std::weak_ptr<Node> m_target;
};
