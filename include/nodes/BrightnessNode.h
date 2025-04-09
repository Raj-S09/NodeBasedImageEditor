#pragma once

#include <string>
#include <imgui.h>
#include "core/Node.h"

class BrightnessNode : public Node
{
public:
    BrightnessNode(int id, const std::string &name);

    void draw(); // this will render the UI
    void setBrightness(float value);
    float getBrightness() const;

    cv::Mat render(const cv::Mat &input);

private:
    float brightness = 1.0f; // Default value (no change)
};