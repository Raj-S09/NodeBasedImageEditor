#include "nodes/BrightnessNode.h"
#include <imgui.h>

BrightnessNode::BrightnessNode(int id, const std::string &name)
    : Node(id, name, Node::Type::Processing) {}

void BrightnessNode::draw()
{
    ImGui::PushID(this);
    ImGui::BeginGroup();
    ImGui::Text("%s", getName().c_str());
    ImGui::SliderFloat("Brightness", &brightness, 0.0f, 2.0f);
    ImGui::EndGroup();
    ImGui::PopID();
}

void BrightnessNode::setBrightness(float value) {
    brightness = value;
}

float BrightnessNode::getBrightness() const {
    return brightness;
}

cv::Mat BrightnessNode::render(const cv::Mat& input) {
    cv::Mat output;
    input.convertTo(output, -1, brightness, 0);  // scale, offset
    return output;
}