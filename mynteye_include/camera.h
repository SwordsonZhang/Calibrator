#ifndef MYNTEYE_API_CAMERA_H_
#define MYNTEYE_API_CAMERA_H_
#pragma once

#include <memory>
#include <vector>

#include <opencv2/core/core.hpp>

#include "callback.h"
#include "camera_information.h"
#include "imudata.h"
#include "init_parameters.h"
#include "mynteye.h"
#include "resolution.h"

namespace mynteye {

class CameraPrivate;

/**
 * The main class to use the MYNT EYE camera.
 */
class MYNTEYE_API Camera {
public:
    /** Constructor. */
    Camera();
    /** Destructor. */
    ~Camera();

    /**
     * Sets mode.
     * default: ::MODE_AUTO_DETECT
     * @param mode the compute mode.
     * @see ::Mode
     */
    void SetMode(const Mode &mode);

    /**
     * Sets scale factor to the grabbed images.
     * @param scale the scale factor.
     */
    void SetScale(float scale);

    /**
     * Opens the MYNE EYE camera.
     * @return ::SUCCESS if ok, otherwise error.
     */
    ErrorCode Open(const InitParameters &params);

    /**
     * Tests if the camera is opened.
     * @return `true` if opened.
     */
    bool IsOpened();

    /**
     * Sets framerate & IMU frequency.
     * @return ::SUCCESS if ok, otherwise failed.
     * @note Only supported on Linux now.
     */
    ErrorCode SetRate(const Rate &rate);

    /**
     * Tests if auto-exposure is enabled.
     * @return `true` if enabled, 'false' if manual-exposure or failed.
     */
    bool IsAutoExposureEnabled();

    /**
     * Sets auto-exposure enabled or not.
     * @param enabled `true` to enable auto-exposure, `false` to enable manual-exposure.
     * @return ::SUCCESS if ok, otherwise failed.
     * @note If auto-exposure is enabled, max-gain, max-brightness and desired-brightness could be set.
     * @note If manual-exposure is enabled, gain, brightness and contrast could be set.
     * @note Only supported on Linux now.
     */
    ErrorCode SetAutoExposureEnabled(bool enabled);

    /**
     * Gets gain value in manual-exposure mode.
     * @return the value in `[0,48]`. `-1` means failed.
     * @note Only supported on Linux now.
     */
    std::int32_t GetGain();

    /**
     * Sets gain value in manual-exposure mode.
     * @param value the gain value in `[0,48]`.
     * @return ::SUCCESS if ok, otherwise failed.
     * @note Only supported on Linux now.
     */
    ErrorCode SetGain(std::int32_t value);

    /**
     * Gets brightness value in manual-exposure mode.
     * @return the value in `[0,240]`. `-1` means failed.
     * @note Only supported on Linux now.
     */
    std::int32_t GetBrightness();

    /**
     * Sets brightness value in manual-exposure mode.
     * @param value the brightness value in `[0,240]`.
     * @return ::SUCCESS if ok, otherwise failed.
     * @note Only supported on Linux now.
     */
    ErrorCode SetBrightness(std::int32_t value);

    /**
     * Gets contrast value in manual-exposure mode.
     * @return the value in `[0,255]`. `-1` means failed.
     * @note Only supported on Linux now.
     */
    std::int32_t GetContrast();

    /**
     * Sets contrast value in manual-exposure mode.
     * @param value the contrast value in `[0,255]`.
     * @return ::SUCCESS if ok, otherwise failed.
     * @note Only supported on Linux now.
     */
    ErrorCode SetContrast(std::int32_t value);

    /**
     * Gets max gain value in auto-exposure mode.
     * @return the value in `[0,48]`. `-1` means failed.
     * @note Only supported on Linux now.
     */
    std::int32_t GetMaxGain();

    /**
     * Sets max gain value in auto-exposure mode.
     * @param value the max gain value in `[0,48]`.
     * @return ::SUCCESS if ok, otherwise failed.
     * @note Only supported on Linux now.
     */
    ErrorCode SetMaxGain(std::int32_t value);

   /**
     * Gets max exposure time value in auto-exposure mode.
     * @return the value in `[0,240]`. `-1` means failed.
     * @note Only supported on Linux now.
     */
    std::int32_t GetMaxExposureTime();

    /**
     * Sets max exposure time value in auto-exposure mode.
     * @param value the max exposure time value in `[0,240]`.
     * @return ::SUCCESS if ok, otherwise failed.
     * @note Only supported on Linux now.
     */
    ErrorCode SetMaxExposureTime(std::int32_t value);

    /**
     * Gets desired brightness value in auto-exposure mode.
     * @return the value in `[0,255]`. `-1` means failed.
     * @note Only supported on Linux now.
     */
    std::int32_t GetDesiredBrightness();

    /**
     * Sets desired brightness value in auto-exposure mode.
     * @param value the desired brightness value in `[0,255]`.
     * @return ::SUCCESS if ok, otherwise failed.
     * @note Only supported on Linux now.
     */
    ErrorCode SetDesiredBrightness(std::int32_t value);

    /**
     * Requests zero drift calibration.
     * @return ::SUCCESS if ok, otherwise failed.
     * @note Only supported on Linux now.
     */
    ErrorCode RequestZeroDriftCalibration();

    /**
     * Activates async grap feature.
     * @param keep_imu_frequency whether keep imu frequency or not.
     */
    void ActivateAsyncGrabFeature(bool keep_imu_frequency = false);

    /**
     * Deactivates async grap feature.
     */
    void DeactivateAsyncGrabFeature();

    /**
     * Tests if the async grap feature is activated.
     * @return `true` if activated.
     */
    bool IsAsyncGrabFeatureActivated();

    /**
     * Activates depth map feature.
     */
    void ActivateDepthMapFeature();

    /**
     * Deactivates depth map feature.
     */
    void DeactivateDepthMapFeature();

    /**
     * Tests if the depth map feature is activated.
     * @return `true` if activated.
     */
    bool IsDepthMapFeatureActivated();

    /**
     * Activates point cloud feature.
     */
    void ActivatePointCloudFeature();

    /**
     * Deactivates point cloud feature.
     */
    void DeactivatePointCloudFeature();

    /**
     * Tests if the point cloud feature is activated.
     * @return `true` if activated.
     */
    bool IsPointCloudFeatureActivated();

    /**
     * Sets grab error callback.
     */
    void SetGrabErrorCallback(GrabErrorCallback callback);

    /**
     * Sets process grab callbacks.
     */
    void SetGrabProcessCallbacks(
        GrabPreProcessCallback pre_callback,
        GrabPostProcessCallback post_callback);

    /**
     * Sets process rectification callbacks.
     */
    void SetRectifyProcessCallbacks(
        RectifyPreProcessCallback pre_callback,
        RectifyPostProcessCallback post_callback);

    /**
     * Sets process depth map callbacks.
     */
    void SetDepthMapProcessCallbacks(
        DepthMapPreProcessCallback pre_callback,
        DepthMapPostProcessCallback post_callback);

    /**
     * Sets process point cloud callbacks.
     */
    void SetPointCloudProcessCallbacks(
        PointCloudPreProcessCallback pre_callback,
        PointCloudPostProcessCallback post_callback);

    /**
     * Grabs the new image, and process it.
     * @note The grabbing function is typically called in the main loop.
     * @note If ActivateAsyncGrabFeature(), you should SetGrabErrorCallback() to listen the grab error.
     *       And this method only return ::ERROR_CAMERA_GRAB_FAILED if there is not a new frame (it will block a moment to wait for grabbing).
     * @return ::SUCCESS if ok, otherwise error.
     */
    ErrorCode Grab();

    /**
     * Retrieves a image of wanted type.
     * @param mat the Mat to store the image.
     * @param view defines the image type wanted, see ::View.
     * @return ::SUCCESS if ok, otherwise error.
     * @note The retrieve function should be called after the function Camera::Grab.
     */
    ErrorCode RetrieveImage(cv::Mat &mat, const View &view = View::VIEW_LEFT);

    /**
     * Retrieves the IMU datas.
     * @param imudatas the given IMU datas.
     * @return ::SUCCESS if ok, otherwise error.
     */
    ErrorCode RetrieveIMUData(std::vector<IMUData> &imudatas);

    /**
     * Retrieves the IMU datas.
     * @param imudatas the given IMU datas.
     * @param timestamp the hardware timestamp which elapsed after camera working, in unit 0.1ms.
     * @return ::SUCCESS if ok, otherwise error.
     */
    ErrorCode RetrieveIMUData(std::vector<IMUData> &imudatas, std::uint32_t &timestamp);

    /**
     * Returns the lastest hardware timestamp which indicates when retrieved
     * the raw images and imu datas. It's the elapsed time after camera working, in unit 0.1ms.
     * @return the current image size.
     */
    std::uint32_t GetTimestamp();

    /**
     * Returns the current image size.
     * @return the current image size.
     */
    Resolution GetResolution();

    /**
     * Returns the camera informations.
     * @return the camera informations.
     */
    CameraInformation GetCameraInformation();

    /**
     * Returns the calibration parameters.
     * @return the calibration parameters.
     */
    CalibrationParameters GetCalibrationParameters();

    /**
     * Returns the dropped count in some process.
     * @return the dropped count in some process.
     */
    std::uint64_t GetDroppedCount(const Process &proc);

    /**
     * Closes the camera and free the memory.
     */
    void Close();

    /**
     * Activates plugin.
     * @param libpath the plugin library path.
     */
    void ActivatePlugin(const std::string &libpath);

    /**
     * Deactivates plugin.
     */
    void DeactivatePlugin();

    /**
     * Tests if plugin is activated.
     * @return `true` if activated.
     */
    bool IsPluginActivated();

    /**
     * Tests if firmware is latest.
     * @return `true` if latest.
     */
    bool IsFirmwareLatest();

    /**
     * Returns the SDK root directory.
     * @return the SDK root directory.
     */
    static std::string GetSDKRoot();

    /**
     * Returns the SDK version.
     * @return the SDK version.
     */
    static std::string GetSDKVersion();

private:
    std::unique_ptr<CameraPrivate> d_ptr;

    friend class CameraPrivate;
};

}  // namespace mynteye

#endif  // MYNTEYE_API_CAMERA_H_
