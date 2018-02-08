#ifndef MYNTEYE_BASE_CAMERA_INFORMATION_H_
#define MYNTEYE_BASE_CAMERA_INFORMATION_H_
#pragma once

#include <string>

#include "mynteye.h"

namespace mynteye {

/**
 * Camera information.
 */
struct MYNTEYE_API CameraInformation {

    /**
     * The serial number.
     */
    std::string serial;

    /**
     * The firmware version.
     */
    std::string version;

    /**
     * The product name.
     */
    std::string product;

    /**
     * The manufacturer name.
     */
    std::string manufacturer;

    /**
     * The product id.
     */
    uint16_t product_id;

    /**
     * The vendor id.
     */
    uint16_t vendor_id;

    /**
     * Loads the camera information from a file.
     * @param filepath the file path from which the information will be loaded.
     * @return ::SUCCESS if ok, otherwise error.
     */
    ErrorCode Load(const std::string &filepath);

    /**
     * Saves the camera information into a file.
     * @param filepath the file path in which the information will be stored.
     * @return ::SUCCESS if ok, otherwise error.
     */
    ErrorCode Save(const std::string &filepath);
};

}  // namespace mynteye

MYNTEYE_API std::ostream &operator<<(std::ostream &os, const mynteye::CameraInformation &info);

#endif  // MYNTEYE_BASE_CAMERA_INFORMATION_H_
