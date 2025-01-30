#ifndef LSM6DSOX_H
#define LSM6DSOX_H

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_def.h"
#include "spi.h"
#include "main.h"
#include "lsm6dsox_ucf.h"

#define FUNC_CFG_ACCESS_REG 0x01
#define FUNC_CFG_ACCESS_VAL 0x80
#define ACC_CONTROL_REG 0x10
#define ACC_CFG_VAL 0x20
#define GYRO_CONTROL_REG 0x11
#define GYRO_CFG_VAL 0x24
#define MLC0_SRC_REG 0x70

/**
 * @brief Defines states retuned by MLC core
 */
enum State
{
    Closed = 0,
    Opened = 4,
    Movement = 8,
};

/**
 * @brief Enables and configures Accelerometer and Gyroscope on LSM6DSOX
 */
void lsm6dsox_configure(void);

/**
 * @brief Sends the entire .ucf configuration file to the LSM6DSOX
 */
void lsm6dsox_load_ucf(void);

#endif