#ifndef LSM6DSOX_H
#define LSM6DSOX_H

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_def.h"
#include "main.h"
#include "lsm6dsox_ucf.h"

// Sensor registers
#define FUNC_CFG_ACCESS_REG 0x01
#define FUNC_CFG_ACCESS_SET 0x80
#define FUNC_CFG_ACCESS_RESET 0x00
#define MLC0_SRC_REG 0x70

// Enum for sensor states
enum State
{
    Closed = 0,
    Opened = 4,
    Movement = 8,
};

// SPI handle is initialized in main.c
extern SPI_HandleTypeDef hspi1;

/**
 * @brief Reads a single register value from the LSM6DSOX via SPI
 * @param reg: Register address to read
 * @param data: Pointer to buffer where read data will be stored
 * @return Status when reading from register.
 */
HAL_StatusTypeDef lsm6dsox_spi_read(uint8_t reg, uint8_t *data);

/**
 * @brief Sends a single register-value pair to the LSM6DSOX via SPI
 * @param reg: Register address (8-bit)
 * @param data: Value to write (8-bit)
 */
HAL_StatusTypeDef lsm6dsox_spi_write(uint8_t reg, uint8_t data);

/**
 * @brief Sends the entire UCF configuration file to the LSM6DSOX sensor
 */
void lsm6dsox_load_ucf();

#endif