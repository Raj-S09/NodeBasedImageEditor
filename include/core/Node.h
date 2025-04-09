#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Pin.h"
#include <imgui.h>
#include <opencv2/opencv.hpp>

class Node
{
public:
    enum class Type
    {
        Input,
        Processing,
        Output
    };

    Node(int id, const std::string &name, Type type);
    virtual ~Node() = default;

    int getId() const;
    std::string getName() const;
    Type getType() const;

    std::vector<std::shared_ptr<Pin>> &getInputPins();
    std::vector<std::shared_ptr<Pin>> &getOutputPins();

    void addInputPin(const std::shared_ptr<Pin> &pin);
    void addOutputPin(const std::shared_ptr<Pin> &pin);

    virtual void draw();
    cv::Mat render(const cv::Mat& input);

    std::shared_ptr<Pin> getPinById(int pinId) const;

    void setPosition(const ImVec2 &pos);
    ImVec2 getPosition() const;

private:
    int id;
    std::string name;
    Type type;

    std::vector<std::shared_ptr<Pin>> inputPins;
    std::vector<std::shared_ptr<Pin>> outputPins;

    ImVec2 position;
};