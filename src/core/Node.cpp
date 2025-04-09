#include "core/Node.h"
#include <imgui.h>

Node::Node(int id, const std::string &name, Type type)
    : id(id), name(name), type(type) {}

int Node::getId() const { return id; }

std::string Node::getName() const { return name; }

Node::Type Node::getType() const { return type; }

std::vector<std::shared_ptr<Pin>> &Node::getInputPins() { return inputPins; }

std::vector<std::shared_ptr<Pin>> &Node::getOutputPins() { return outputPins; }

void Node::addInputPin(const std::shared_ptr<Pin> &pin)
{
    inputPins.push_back(pin);
}

void Node::addOutputPin(const std::shared_ptr<Pin> &pin)
{
    outputPins.push_back(pin);
}

void Node::draw()
{
    // Default draw, override in subclass
    ImGui::Text("Node: %s", name.c_str());
}

void Node::setPosition(const ImVec2 &pos)
{
    position = pos;
}

ImVec2 Node::getPosition() const
{
    return position;
}

std::shared_ptr<Pin> Node::getPinById(int pinId) const
{
    for (const auto &pin : inputPins)
        if (pin->getId() == pinId)
            return pin;
    for (const auto &pin : outputPins)
        if (pin->getId() == pinId)
            return pin;
    return nullptr;
}