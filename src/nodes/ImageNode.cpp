#include <opencv2/opencv.hpp>
#include "nodes/ImageNode.h"
#include <imgui.h>

ImageNode::ImageNode(int id, const std::string& path, GLuint textureID)
    : Node(id, path, Node::Type::Input), path(path), textureID(textureID) {
    position = ImVec2(50, 50); // default position
    imageMat = cv::imread(path, cv::IMREAD_UNCHANGED);
}

void ImageNode::draw() {
    ImGui::SetCursorScreenPos(ImVec2(ImGui::GetCursorScreenPos().x + position.x, ImGui::GetCursorScreenPos().y + position.y));
    ImGui::PushID(this);
    ImGui::BeginGroup();

    std::string filename = path.substr(path.find_last_of("/\\") + 1);
    ImGui::Text("%s", filename.c_str());

    ImTextureID tex_id = (ImTextureID)(uintptr_t)textureID;
    ImGui::Image(tex_id, ImVec2(200, 200), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(0.2f, 0.2f, 0.2f, 1));

    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
        ImVec2 delta = ImGui::GetIO().MouseDelta;
        position.x += delta.x;
        position.y += delta.y;
    }

    ImGui::EndGroup();
    ImGui::PopID();
}

const std::string& ImageNode::getPath() const {
    return path;
}

GLuint ImageNode::getTextureID() const {
    return textureID;
}

ImVec2 ImageNode::getPosition() const {
    return position;
}

void ImageNode::setPosition(const ImVec2& newPos) {
    position = newPos;
}

// In ImageNode.cpp
cv::Mat ImageNode::getImage() const {
    return imageMat; // Store imageMat when loading from OpenCV
}