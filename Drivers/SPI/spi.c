#include "spi.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;

HAL_StatusTypeDef lsm6dsox_spi_write(uint8_t reg, uint8_t data)
{
    uint8_t tx_buffer[2];
    tx_buffer[0] = reg & 0x7F;
    tx_buffer[1] = data;

    HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_RESET);

    HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, tx_buffer, 2, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_SET);

    return status;
}

HAL_StatusTypeDef lsm6dsox_spi_read(uint8_t reg, uint8_t *data)
{
    uint8_t tx_buffer[2];
    uint8_t rx_buffer[2];

    tx_buffer[0] = reg | 0x80;
    tx_buffer[1] = 0x00;

    HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_RESET);

    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(&hspi1, tx_buffer, rx_buffer, 2, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_SET);

    *data = rx_buffer[1];

    return status;
}