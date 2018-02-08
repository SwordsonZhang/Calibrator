#ifndef MYNTEYE_BASE_IMUDATA_H_
#define MYNTEYE_BASE_IMUDATA_H_
#pragma once

#include "mynteye.h"

namespace mynteye {

/**
 * IMU (inertial measurement unit) data.
 */
struct MYNTEYE_API IMUData {
    /**
     * Time which elapsed after camera working, in unit 0.1ms.
     * @note time = timestamp + time_offset
     * @see Camera::RetrieveIMUData()
     */
    std::uint32_t time;
    /**
     * Time offset before retrieve IMU data, in unit 0.1ms.
     */
    std::int16_t time_offset;
    //@{
    /**
     * Accelerometer data for 3-axis: x, y, z.
     * @see accel_x, accel_y, accel_z
     */
    float accel_x;
    float accel_y;
    float accel_z;
    //@}
    //@{
    /**
     * Gyroscope data for 3-axis: x, y, z.
     * @see gyro_x, gyro_y, gyro_z
     */
    float gyro_x;
    float gyro_y;
    float gyro_z;
    //@}
};

}  // namespace mynteye

MYNTEYE_API std::ostream &operator<<(std::ostream &os, const mynteye::IMUData &data);

#endif  // MYNTEYE_BASE_IMUDATA_H_
