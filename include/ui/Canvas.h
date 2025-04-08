#pragma once

#include <vector>
#include <memory>
#include "core/Node.h"
#include "core/Connection.h"
#include <imgui.h>

class Canvas {
public:
    void addNode(const std::shared_ptr<Node>& node);
    void addConnection(const std::shared_ptr<Connection>& connection);

    void draw();

    const std::vector<std::shared_ptr<Node>>& getNodes() const;
    const std::vector<std::shared_ptr<Connection>>& getConnections() const;

private:
    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<Connection>> connections;

    // 👇 Add these!
    ImVec2 demoNodePos = ImVec2(100, 100);
    ImVec2 demoNodeSize = ImVec2(200, 100);
    bool demoNodeSelected = false;
};