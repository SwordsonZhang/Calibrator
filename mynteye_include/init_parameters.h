#ifndef MYNTEYE_BASE_INIT_PARAMETERS_H_
#define MYNTEYE_BASE_INIT_PARAMETERS_H_
#pragma once

#include <string>

#include "calibration_parameters.h"
#include "mynteye.h"

namespace mynteye {

/**
 * Parameters for MYNT EYE initialization.
 */
struct MYNTEYE_API InitParameters {

    /**
     * Camera name or index.
     *
     * default values:
     *   - Windows: MYNTEYE
     *   - Mac: 0
     *   - Linux: 0
     */
    std::string name;

    /**
     * Camera framerate & IMU frequency.
     *
     * default: ::RATE_LAST, ignored
     *
     * @note Only supported on Linux now.
     */
    Rate rate;

    /**
     * Calibration parameters.
     *
     * If not specified, we will download from our server by serial number.
     *
     * default: nullptr
     */
    const CalibrationParameters *clib_params;

    /** Constructor. */
    InitParameters();
    /** Constructor. */
    InitParameters(const std::string &name,
        const CalibrationParameters *clib_params = nullptr);
    /** Constructor. */
    InitParameters(const std::string &name,
        const Rate &rate,
        const CalibrationParameters *clib_params = nullptr);

    /** Destructor. */
    ~InitParameters();

    /**
     * Loads the values of the parameters contained in a file.
     * @param filename the path to the file from which the parameters will be loaded.
     * @return ::SUCCESS if ok, otherwise error.
     */
    ErrorCode Load(const std::string &filename);

    /**
     * Saves the current bunch of parameters into a file.
     * @param filename the path to the file in which the parameters will be stored.
     * @return ::SUCCESS if ok, otherwise error.
     */
    ErrorCode Save(const std::string &filename);
};

}  // namespace mynteye

MYNTEYE_API std::ostream &operator<<(std::ostream &os, const mynteye::InitParameters &params);

#endif  // MYNTEYE_BASE_INIT_PARAMETERS_H_
