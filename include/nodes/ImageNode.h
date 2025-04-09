#pragma once

#include <string>
#include <imgui.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>

#include "core/Node.h"

class ImageNode : public Node
{
public:
    ImageNode(int id, const std::string &path, GLuint textureID);

    void draw();
    const std::string &getPath() const;
    GLuint getTextureID() const;
    ImVec2 getPosition() const;
    void setPosition(const ImVec2 &newPos);
    cv::Mat getImage() const;

private:
    std::string path;
    GLuint textureID;
    ImVec2 position;
    cv::Mat imageMat;
};