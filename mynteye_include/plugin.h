#ifndef MYNTEYE_API_PLUGIN_H_
#define MYNTEYE_API_PLUGIN_H_
#pragma once

#include <vector>

#include <opencv2/core/core.hpp>

#include "imudata.h"
#include "mynteye.h"

namespace mynteye {

class Camera;

/**
 * The plugin which could implement processing by yourself.
 */
class MYNTEYE_API Plugin {
public:
    Plugin() = default;
    virtual ~Plugin() = 0;

    /**
     * Called when plugin created.
     * @param camera the MYNT EYE camera.
     */
    virtual void OnCreate(Camera *camera) {
        camera_ = camera;
    }

    /**
     * Called when camera opened.
     * @param code ::SUCCESS if ok, otherwise error.
     */
    virtual void OnOpen(const ErrorCode &code) {}

    /**
     * Called when camera grabbed.
     * @param code ::SUCCESS if ok, otherwise error.
     */
    virtual void OnGrab(const ErrorCode &code) {}

    /**
     * Called when camera retrieved image.
     * @param mat the Mat to store the image.
     * @param view defines the image type wanted, see ::View.
     * @param code ::SUCCESS if ok, otherwise error.
     */
    virtual void OnRetrieveImage(cv::Mat &mat, const View &view, const ErrorCode &code) {}

    /**
     * Called when camera retrieved IMU datas.
     * @param imudatas the given IMU datas.
     * @param timestamp the timestamp which elapsed after MYNTEYE working with unit 0.1ms.
     * @param code ::SUCCESS if ok, otherwise error.
     * @note time_elapsed_ms = timestamp / 10
     */
    virtual void OnRetrieveIMUData(std::vector<IMUData> &imudatas, std::uint32_t &timestamp, const ErrorCode &code) {}

    /**
     * Called when camera closed.
     */
    virtual void OnClose() {}

    /**
     * Called before process grabbed images.
     * @note This method is called in a standalone processing thread.
     */
    virtual void OnProcessGrab(cv::Mat &left_raw, cv::Mat &right_raw) {}

    /**
     * Called before process rectification.
     * @note This method is called in a standalone processing thread.
     * @return true if processed by yourself. Then it won't process rectification any more in SDK.
     */
    virtual bool OnProcessRecify(
            const cv::Mat &left_raw, const cv::Mat &right_raw,
            cv::Mat &left_rectified, cv::Mat &right_rectified) {
        return false;
    }

    /**
     * Called before process depth map.
     * @note This method is called in a standalone processing thread.
     * @return true if processed by yourself. Then it won't process depth map any more in SDK.
     */
    virtual bool OnProcessDepthMap(
            const cv::Mat &left_rectified, const cv::Mat &right_rectified,
            cv::Mat &depthmap) {
        return false;
    }

    /**
     * Called before process point cloud.
     * @note This method is called in a standalone processing thread.
     * @return true if processed by yourself. Then it won't process point cloud any more in SDK.
     */
    virtual bool OnProcessPointCloud(
            const cv::Mat &depthmap, cv::Mat &pointcloud) {
        return false;
    }

protected:
    Camera *camera_;
};

inline Plugin::~Plugin() = default;

using plugin_create_t = Plugin *();
using plugin_destroy_t = void (Plugin *);

}  // namespace mynteye

extern "C" {

/**
 * Create this plugin.
 */
MYNTEYE_API mynteye::Plugin *plugin_create();

/**
 * Destroy this plugin.
 */
MYNTEYE_API void plugin_destroy(mynteye::Plugin *plugin);

}

#endif  // MYNTEYE_API_PLUGIN_H_
