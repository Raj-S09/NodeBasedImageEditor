#include "ui/PropertiesPanel.h"

void PropertiesPanel::setSelectedNode(const std::shared_ptr<Node>& node) {
    selectedNode = node;
}

void PropertiesPanel::draw() {
    // Later: render sliders, labels, etc. using ImGui based on selectedNode
}