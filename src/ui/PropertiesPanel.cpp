#include "ui/PropertiesPanel.h"
#include "nodes/BrightnessNode.h"
#include <imgui.h>

void PropertiesPanel::draw(const std::shared_ptr<Node>& selectedNode) {
    if (!selectedNode) {
        ImGui::Text("No node selected");
        return;
    }

    ImGui::Text("Selected Node: %s", selectedNode->getName().c_str());

    // Show brightness slider if it's a BrightnessNode
    if (selectedNode->getType() == Node::Type::Processing) {
        if (auto brightnessNode = std::dynamic_pointer_cast<BrightnessNode>(selectedNode)) {
            float brightness = brightnessNode->getBrightness();
            if (ImGui::SliderFloat("Brightness", &brightness, 0.0f, 2.0f)) {
                brightnessNode->setBrightness(brightness);
            }
        }
    }
}