#pragma once

#include <memory>
#include "core/Node.h"

class PropertiesPanel {
public:
    void setSelectedNode(const std::shared_ptr<Node>& node);
    void draw(const std::shared_ptr<Node>& selectedNode);

private:
    std::shared_ptr<Node> selectedNode;
};