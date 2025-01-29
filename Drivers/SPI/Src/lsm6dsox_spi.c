/**
 * @brief Sends a single register-value pair to the LSM6DSOX via SPI.
 * @param reg Register address (8-bit).
 * @param value Value to write (8-bit).
 */
HAL_StatusTypeDef LSM6DSOX_Write(uint8_t register, uint8_t data)
{
    uint8_t tx_buffer[2];

    // SPI protocol for LSM6DSOX: MSB = 0 for write, followed by 7-bit register address
    tx_buffer[0] = register & 0x7F;
    tx_buffer[1] = data;

    HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_RESET);

    // Transmit data over SPI
    HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, tx_buffer, 2, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_SET);

    return status;
}

/**
 * @brief Reads a single register value from the LSM6DSOX via SPI.
 * @param reg Register address to read.
 * @return The value read from the register.
 */
HAL_StatusTypeDef LSM6DSOX_Read(uint8_t reg, uint8_t *data)
{
    uint8_t tx_buffer[2];
    uint8_t rx_buffer[2];

    // SPI protocol for LSM6DSOX: MSB = 1 for read, followed by 7-bit register address
    tx_buffer[0] = reg | 0x80; // Set MSB to indicate read operation
    tx_buffer[1] = 0x00;       // Dummy byte to generate clock for reading

    // Select the sensor (assert NSS low)
    HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_RESET); // Replace GPIOx and GPIO_PIN_NSS with your NSS pin

    // Transmit and receive data over SPI
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(&hspi1, tx_buffer, rx_buffer, 2, HAL_MAX_DELAY);

    // Deselect the sensor (assert NSS high)
    HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_SET);

    // Store the received data
    *data = rx_buffer[1];

    return status;
}
