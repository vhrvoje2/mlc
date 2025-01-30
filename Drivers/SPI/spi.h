#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_def.h"

/**
 * @brief Sends a single register-value pair to the LSM6DSOX via SPI
 * @param reg Register address
 * @param data Pointer to buffer where data will be stored
 * @return Read status
 */
HAL_StatusTypeDef lsm6dsox_spi_read(uint8_t reg, uint8_t *data);

/**
 * @brief Reads a single register value from the LSM6DSOX via SPI
 * @param reg Register address
 * @param value Value to write
 * @return Write status
 */
HAL_StatusTypeDef lsm6dsox_spi_write(uint8_t reg, uint8_t data);

#endif
