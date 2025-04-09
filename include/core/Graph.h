#pragma once

#include <vector>
#include <memory>
#include "core/Node.h"
#include "core/Connection.h"
#include <opencv2/opencv.hpp>

class Graph {
public:
    void addNode(const std::shared_ptr<Node>& node);
    void addConnection(const std::shared_ptr<Connection>& connection);

    std::vector<std::shared_ptr<Node>>& getNodes();
    std::vector<std::shared_ptr<Connection>>& getConnections();

    std::shared_ptr<Node> getNodeById(int id) const;
    cv::Mat render();

private:
    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<Connection>> connections;
};