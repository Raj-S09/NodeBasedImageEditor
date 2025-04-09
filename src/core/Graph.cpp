#include "core/Graph.h"
#include "nodes/BrightnessNode.h"
#include "nodes/ImageNode.h"

void Graph::addNode(const std::shared_ptr<Node>& node) {
    nodes.push_back(node);
}

void Graph::addConnection(const std::shared_ptr<Connection>& connection) {
    connections.push_back(connection);
}

std::vector<std::shared_ptr<Node>>& Graph::getNodes() {
    return nodes;
}

std::vector<std::shared_ptr<Connection>>& Graph::getConnections() {
    return connections;
}

std::shared_ptr<Node> Graph::getNodeById(int id) const {
    for (const auto& node : nodes) {
        if (node->getId() == id) return node;
    }
    return nullptr;
}

cv::Mat Graph::render() {
    cv::Mat image;

    // Step 1: Find the image input node
    for (auto& node : nodes) {
        if (auto imageNode = std::dynamic_pointer_cast<ImageNode>(node)) {
            image = imageNode->getImage();
            break;
        }
    }

    if (image.empty()) return image;

    // Step 2: Apply all brightness nodes in order
    for (auto& node : nodes) {
        if (auto brightnessNode = std::dynamic_pointer_cast<BrightnessNode>(node)) {
            image = brightnessNode->render(image);
        }
    }

    return image;
}