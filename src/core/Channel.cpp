#include "core/Channel.h"

Channel::Channel(const cv::Mat &data, const std::string &label)
    : data(data), label(label) {}

const cv::Mat &Channel::getData() const { return data; }

std::string Channel::getLabel() const { return label; }