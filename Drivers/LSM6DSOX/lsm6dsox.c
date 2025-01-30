#include "lsm6dsox.h"

void lsm6dsox_configure(void)
{
    HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_SET);

    if (lsm6dsox_spi_write(FUNC_CFG_ACCESS_REG, FUNC_CFG_ACCESS_VAL) != HAL_OK)
    {
        HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_RESET);
    };

    if (lsm6dsox_spi_write(ACC_CONTROL_REG, ACC_CFG_VAL) != HAL_OK)
    {
        HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_RESET);
    };

    if (lsm6dsox_spi_write(GYRO_CONTROL_REG, GYRO_CFG_VAL) != HAL_OK)
    {
        HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_RESET);
    };
}

void lsm6dsox_load_ucf(void)
{
    size_t ucf_size = sizeof(movement) / sizeof(movement[0]);
    size_t i;
    for (i = 0; i < ucf_size; i += 2)
    {
        uint8_t reg = movement->address;
        uint8_t value = movement->data;

        if (lsm6dsox_spi_write(reg, value) != HAL_OK)
        {
            HAL_GPIO_WritePin(CPU_LED_GPIO_Port, CPU_LED_Pin, GPIO_PIN_SET);
        };
    }

    HAL_GPIO_WritePin(CPU_LED_GPIO_Port, CPU_LED_Pin, GPIO_PIN_RESET);
}
