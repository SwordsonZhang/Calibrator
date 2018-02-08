#ifndef MYNTEYE_API_CALLBACK_H_
#define MYNTEYE_API_CALLBACK_H_
#pragma once

#include <functional>

#include <opencv2/core/core.hpp>

#include "mynteye.h"

namespace mynteye {

/** Error callback. */
using ErrorCallback  = std::function<void(const ErrorCode &code)>;

/** Process feature callback with one image. */
using ProcessCallback  = std::function<void(cv::Mat &image)>;
/** Process feature callback with two images. */
using ProcessCallback2 = std::function<void(cv::Mat &left, cv::Mat &right)>;

/**
 * Grab error callback
 * @param code
 */
using GrabErrorCallback = ErrorCallback;

/**
 * Pre process grab callback
 */
using GrabPreProcessCallback = std::function<void()>;
/**
 * Post process grab callback
 * @param left_raw
 * @param right_raw
 */
using GrabPostProcessCallback = ProcessCallback2;

/**
 * Pre process rectification callback
 * @param left_raw
 * @param right_raw
 */
using RectifyPreProcessCallback = ProcessCallback2;
/**
 * Post process rectification callback
 * @param left_rectified
 * @param right_rectified
 */
using RectifyPostProcessCallback = ProcessCallback2;

/**
 * Pre process depth map callback
 * @param left_rectified
 * @param right_rectified
 */
using DepthMapPreProcessCallback = ProcessCallback2;
/**
 * Post process depth map callback
 * @param depthmap
 */
using DepthMapPostProcessCallback = ProcessCallback;

/**
 * Pre process point cloud callback
 * @param depthmap
 */
using PointCloudPreProcessCallback = ProcessCallback;
/**
 * Post process point cloud callback
 * @param pointcloud
 */
using PointCloudPostProcessCallback = ProcessCallback;

}  // namespace mynteye

#endif  // MYNTEYE_API_CALLBACK_H_
