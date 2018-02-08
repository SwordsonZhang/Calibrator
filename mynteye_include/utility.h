#ifndef MYNTEYE_BASE_UTILITY_H_
#define MYNTEYE_BASE_UTILITY_H_
#pragma once

#include <string>

#include <opencv2/core/core.hpp>

#include "mynteye.h"

namespace mynteye {

MYNTEYE_API std::string Exec(const char *cmd);

MYNTEYE_API cv::Rect DrawInfo(const cv::Mat& im, const std::string &text,
    const Gravity &gravity = Gravity::TOP_LEFT, const int &margin = 5,
    const int &offset_x = 0, const int &offset_y = 0);

}  // namespace mynteye

#endif  // MYNTEYE_BASE_UTILITY_H_
