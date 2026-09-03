
#include "app/app.hpp"

#include <cstdint>

#include "adc.h"
#include "fdcan.h"
#include "gn10_can/core/fdcan_bus.hpp"
#include "gn10_can/devices/power_manager_server.hpp"
#include "gn10_can/devices/power_manager_types.hpp"
#include "gn10_stm32_fdcan_driver/can_callback_helper.hpp"
#include "gn10_stm32_fdcan_driver/fdcan_driver.hpp"

namespace {

gn10_can::devices::power_manager::Config config{false, 1000};

gn10_can::drivers::FDCANDriver fdcan_driver(&hfdcan1);
gn10_can::FDCANBus fdcan_bus(fdcan_driver);
gn10_can::devices::PowerManagerServer server(fdcan_bus, 1);

uint16_t adc_raw_value[4];
uint32_t sensor_update_last_tick;

constexpr uint32_t HEARTBEAT_TOGGLE_INTERVAL_MS = 200;

void update_heartbeat_led()
{
    static uint32_t last_time = 0;
    if ((HAL_GetTick() - last_time) >= HEARTBEAT_TOGGLE_INTERVAL_MS) {
        last_time = HAL_GetTick();
        HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
    }
}

}  // namespace

void setup()
{
    fdcan_driver.init();
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_raw_value, 4) != HAL_OK) {
        Error_Handler();
    }
    sensor_update_last_tick = HAL_GetTick();
}

void loop()
{
    const uint32_t now_ms = HAL_GetTick();
    if (server.get_new_init(config)) {
        HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
    }
    if ((now_ms - sensor_update_last_tick) >= config.sensor_rate_ms) {
        sensor_update_last_tick = now_ms;
        std::array<float, 3> voltage_in{};
        float voltage_out;
        voltage_out   = static_cast<float>(adc_raw_value[0]) * 3.3f / 0b111111111111 / 11.0f;
        voltage_in[0] = static_cast<float>(adc_raw_value[3]) * 3.3f / 0b111111111111 / 11.0f;
        voltage_in[1] = static_cast<float>(adc_raw_value[2]) * 3.3f / 0b111111111111 / 11.0f;
        voltage_in[2] = static_cast<float>(adc_raw_value[1]) * 3.3f / 0b111111111111 / 11.0f;
        std::array<float, 4> voltages{voltage_in[0], voltage_in[1], voltage_in[2], voltage_out};
        server.set_voltages(voltages);
    }

    update_heartbeat_led();
}

extern "C" {
// C言語側の関数のオーバーライド
/**
 * @brief Receive callback for FDCAN FIFO0.
 */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo0ITs)
{
    (void)RxFifo0ITs;
    if (process_fdcan_fifo(hfdcan, &hfdcan1, fdcan_bus, FDCAN_RX_FIFO0)) return;
}

/**
 * @brief Receive callback for FDCAN FIFO1.
 */
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo1ITs)
{
    (void)RxFifo1ITs;
    if (process_fdcan_fifo(hfdcan, &hfdcan1, fdcan_bus, FDCAN_RX_FIFO1)) return;
}
}
