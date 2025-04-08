#include <iostream>
#include "core/Node.h"
#include "core/Pin.h"
#include "core/Connection.h"

int main()
{
    auto node1 = std::make_shared<Node>(1, "Input Node", Node::Type::Input);
    auto node2 = std::make_shared<Node>(2, "Brightness Node", Node::Type::Processing);

    auto outPin = std::make_shared<Pin>(1, "Output", Pin::PinType::Output, node1);
    auto inPin = std::make_shared<Pin>(2, "Input", Pin::PinType::Input, node2);

    node1->addOutputPin(outPin);
    node2->addInputPin(inPin);

    Connection connection(outPin, inPin);

    std::cout << "Connected " << connection.getFromPin()->getOwner()->getName()
              << " to " << connection.getToPin()->getOwner()->getName() << std::endl;

    return 0;
}