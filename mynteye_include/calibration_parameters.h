#ifndef MYNTEYE_BASE_CALIBRATION_PARAMETERS_H_
#define MYNTEYE_BASE_CALIBRATION_PARAMETERS_H_
#pragma once

#include <string>

#include <opencv2/core/core.hpp>

#include "mynteye.h"

namespace mynteye {

/**
 * Intrinsic parameters of each cameras and extrinsic (translation and rotation).
 */
struct MYNTEYE_API CalibrationParameters {

    // Intrinsic parameters

    /**
     * Input/output left camera matrix.
     * @see cameraMatrix1 parameter of <a href="http://docs.opencv.org/master/d9/d0c/group__calib3d.html#ga246253dcc6de2e0376c599e7d692303a">stereoCalibrate()</a>
     */
    cv::Mat M1;

    /**
     * Input/output lens distortion coefficients for left camera.
     * @see distCoeffs1 parameter of <a href="http://docs.opencv.org/master/d9/d0c/group__calib3d.html#ga246253dcc6de2e0376c599e7d692303a">stereoCalibrate()</a>
     */
    cv::Mat D1;

    /**
     * Input/output right camera matrix.
     * @see cameraMatrix1 parameter of <a href="http://docs.opencv.org/master/d9/d0c/group__calib3d.html#ga246253dcc6de2e0376c599e7d692303a">stereoCalibrate()</a>
     */
    cv::Mat M2;

    /**
     * Input/output lens distortion coefficients for right camera.
     * @see distCoeffs2 parameter of <a href="http://docs.opencv.org/master/d9/d0c/group__calib3d.html#ga246253dcc6de2e0376c599e7d692303a">stereoCalibrate()</a>
     */
    cv::Mat D2;

    // Extrinsic parameters

    /**
     * Output rotation matrix between left and right camera coordinate systems.
     * @see R parameter of <a href="http://docs.opencv.org/master/d9/d0c/group__calib3d.html#ga246253dcc6de2e0376c599e7d692303a">stereoCalibrate()</a>
     */
    cv::Mat R;

    /**
     * Output translation vector between the coordinate systems of the cameras.
     * @see T parameter of <a href="http://docs.opencv.org/master/d9/d0c/group__calib3d.html#ga246253dcc6de2e0376c599e7d692303a">stereoCalibrate()</a>
     */
    cv::Mat T;

    /** Constructor. */
    CalibrationParameters();
    /** Constructor. */
    CalibrationParameters(
        const cv::Mat &M1, const cv::Mat &D1,
        const cv::Mat &M2, const cv::Mat &D2,
        const cv::Mat &R, const cv::Mat &T);

    /** Destructor. */
    ~CalibrationParameters();

    /**
     * Loads the calibration parameters from a file.
     * @param filepath the file path from which the parameters will be loaded.
     * @return ::SUCCESS if ok, otherwise error.
     */
    ErrorCode Load(const std::string &filepath);

    /**
     * Loads the calibration parameters from two different file.
     * @param intrinsic_filepath the file path from which the intrinsic parameters will be loaded.
     * @param extrinsic_filepath the file path from which the extrinsic parameters will be loaded.
     * @return ::SUCCESS if ok, otherwise error.
     */
    ErrorCode Load(const std::string &intrinsic_filepath, const std::string &extrinsic_filepath);

    /**
     * Saves the calibration parameters into a file.
     * @param filepath the file path in which the parameters will be stored.
     * @return ::SUCCESS if ok, otherwise error.
     */
    ErrorCode Save(const std::string &filepath);
};

}  // namespace mynteye

MYNTEYE_API std::ostream &operator<<(std::ostream &os, const mynteye::CalibrationParameters &params);

#endif  // MYNTEYE_BASE_CALIBRATION_PARAMETERS_H_
