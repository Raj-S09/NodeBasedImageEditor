#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class Channel
{
public:
    Channel(const cv::Mat &data, const std::string &label = "");

    const cv::Mat &getData() const;
    std::string getLabel() const;

private:
    cv::Mat data;
    std::string label;
};