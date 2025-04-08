#include "Connection.h"

Connection::Connection(std::shared_ptr<Pin> from, std::shared_ptr<Pin> to)
    : fromPin(from), toPin(to) {}

std::shared_ptr<Pin> Connection::getFromPin() const { return fromPin; }

std::shared_ptr<Pin> Connection::getToPin() const { return toPin; }