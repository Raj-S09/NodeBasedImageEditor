#pragma once

#include <memory>
#include "Pin.h"

class Connection
{
public:
    Connection(std::shared_ptr<Pin> from, std::shared_ptr<Pin> to);

    std::shared_ptr<Pin> getFromPin() const;
    std::shared_ptr<Pin> getToPin() const;

private:
    std::shared_ptr<Pin> fromPin;
    std::shared_ptr<Pin> toPin;
};