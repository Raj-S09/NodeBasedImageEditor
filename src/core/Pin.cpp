#include "Pin.h"
#include "Node.h"

Pin::Pin(int id, const std::string &name, PinType type, std::shared_ptr<Node> owner)
    : id(id), name(name), type(type), owner(owner) {}

int Pin::getId() const { return id; }

std::string Pin::getName() const { return name; }

Pin::PinType Pin::getType() const { return type; }

std::shared_ptr<Node> Pin::getOwner() const { return owner; }