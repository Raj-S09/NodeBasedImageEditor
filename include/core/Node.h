#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Pin.h"

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

    int getId() const;
    std::string getName() const;
    Type getType() const;

    std::vector<std::shared_ptr<Pin>> &getInputPins();
    std::vector<std::shared_ptr<Pin>> &getOutputPins();

    void addInputPin(const std::shared_ptr<Pin> &pin);
    void addOutputPin(const std::shared_ptr<Pin> &pin);

private:
    int id;
    std::string name;
    Type type;

    std::vector<std::shared_ptr<Pin>> inputPins;
    std::vector<std::shared_ptr<Pin>> outputPins;
};