#pragma once

#include <string>
#include <memory>

class Node; // forward declaration

class Pin
{
public:
    enum class PinType
    {
        Input,
        Output
    };

    Pin(int id, const std::string &name, PinType type, std::shared_ptr<Node> owner);

    int getId() const;
    std::string getName() const;
    PinType getType() const;
    std::shared_ptr<Node> getOwner() const;

private:
    int id;
    std::string name;
    PinType type;
    std::shared_ptr<Node> owner;
};