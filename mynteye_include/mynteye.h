/**
 * @defgroup enumerations Public enumeration types
 */
#ifndef MYNTEYE_BASE_MYNTEYE_H_
#define MYNTEYE_BASE_MYNTEYE_H_
#pragma once

#include <cstdint>
#include <ostream>

#define STRINGIFY_HELPER(X) #X
#define STRINGIFY(X) STRINGIFY_HELPER(X)

#ifdef _WIN32
    #define DECL_EXPORT __declspec(dllexport)
    #define DECL_IMPORT __declspec(dllimport)
    #define DECL_HIDDEN
#else
    #define DECL_EXPORT __attribute__((visibility("default")))
    #define DECL_IMPORT __attribute__((visibility("default")))
    #define DECL_HIDDEN __attribute__((visibility("hidden")))
#endif

#ifdef DOXYGEN_WORKING

#define MYNTEYE_API

#else

#ifdef MYNTEYE_EXPORTS
    #define MYNTEYE_API DECL_EXPORT
#else
    #define MYNTEYE_API DECL_IMPORT
#endif

#endif

#if defined(CXX11) || defined(CXX0X)
    #define ENUM(name) enum class name : std::int8_t
#else
    #define ENUM(name) enum name
#endif

/**
 * MYNT EYE namespace
 */
namespace mynteye {

/**
 * @ingroup enumerations
 * @brief List error codes in the MYNT EYE SDK.
 */
ENUM(ErrorCode) {
    /** Standard code for successful behavior. */
    SUCCESS = 0,
    /** Standard code for unsuccessful behavior. */
    ERROR_FAILURE,
    /** File cannot be opened for not exist, not a regular file or any other reason. */
    ERROR_FILE_OPEN_FAILED,
    /** Camera cannot be opened for not plugged or any other reason. */
    ERROR_CAMERA_OPEN_FAILED,
    /** Camera is not opened now. */
    ERROR_CAMERA_NOT_OPENED,
    /** Camera grab the image failed. */
    ERROR_CAMERA_GRAB_FAILED,
    /** Camera retrieve the image failed. */
    ERROR_CAMERA_RETRIEVE_FAILED,
    /** Camera retrieve the image not ready (in computing). */
    ERROR_CAMERA_RETRIEVE_NOT_READY,
    /** Feature is not activiated now. */
    ERROR_FEATURE_NOT_ACTIVATED,
    /** Last guard. */
    ERROR_LAST
};

/**
 * @ingroup enumerations
 * @brief List available modes.
 */
ENUM(Mode) {
    /** Auto detect. */
    MODE_AUTO_DETECT,
    /** CPU. */
    MODE_CPU,
    /** GPU. */
    MODE_GPU,
    /** Last guard. */
    MODE_LAST
};

/**
 * @ingroup enumerations
 * @brief List available views.
 */
ENUM(View) {
    /** Left image, rectified. */
    VIEW_LEFT,
    /** Right image, rectified. */
    VIEW_RIGHT,
    /** Raw left image, unrectified. */
    VIEW_LEFT_UNRECTIFIED,
    /** Raw right image, unrectified. */
    VIEW_RIGHT_UNRECTIFIED,
    /** Depth map, normalized [0,255]. */
    VIEW_DEPTH_MAP,
    /** Depth map, unnormalized. */
    VIEW_DEPTH_MAP_UNNORMALIZED,
    /**
     * Point cloud with OpenCV coordinate system.
     * See here: http://docs.opencv.org/master/d9/d0c/group__calib3d.html#details
     */
    VIEW_POINT_CLOUD,
    /** Last guard. */
    VIEW_LAST
};

/**
 * @ingroup enumerations
 * @brief List rate options.
 */
ENUM(Rate) {
    /** Image 50 FPS, IMU 500 Hz. */
    RATE_50_FPS_500_HZ,
    /** Image 25 FPS, IMU 500 Hz. */
    RATE_25_FPS_500_HZ,
    /** Image 10 FPS, IMU 200 Hz. */
    RATE_10_FPS_200_HZ,
    /** Last guard. */
    RATE_LAST
};

/**
 * @ingroup enumerations
 * @brief List process names.
 */
ENUM(Process) {
    /** Process grab. */
    PROC_GRAB,
    /** Process rectification. */
    PROC_RECTIFY,
    /** Process depth map. */
    PROC_DEPTH_MAP,
    /** Process point cloud. */
    PROC_POINT_CLOUD,
    /** Last guard. */
    PROC_LAST
};

/**
 * @ingroup enumerations
 * @brief List gravity values.
 */
ENUM(Gravity) {
    /** Top left. */
    TOP_LEFT,
    /** Top right. */
    TOP_RIGHT,
    /** Bottom left. */
    BOTTOM_LEFT,
    /** Bottom right. */
    BOTTOM_RIGHT,
    /** Last guard. */
    GRAVITY_LAST
};

}  // namespace mynteye

MYNTEYE_API std::ostream &operator<<(std::ostream &os, const mynteye::ErrorCode &code);
MYNTEYE_API std::ostream &operator<<(std::ostream &os, const mynteye::Mode &mode);
MYNTEYE_API std::ostream &operator<<(std::ostream &os, const mynteye::View &view);
MYNTEYE_API std::ostream &operator<<(std::ostream &os, const mynteye::Rate &rate);
MYNTEYE_API std::ostream &operator<<(std::ostream &os, const mynteye::Process &proc);
MYNTEYE_API std::ostream &operator<<(std::ostream &os, const mynteye::Gravity &gravity);

#endif  // MYNTEYE_BASE_MYNTEYE_H_
