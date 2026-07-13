
#include "logic_power_management_board/Inc/logic_power_management_board.hpp"

#include <cstdint>
//

#include "adc.h"
#include "adc_monitor/Inc/adc_monitor.hpp"
// adc

#include "fdcan/Inc/fdcan_driver.hpp"
#include "gn10_can/core/fdcan_bus.hpp"
#include "gn10_can/devices/power_manager_server.hpp"
#include "gn10_can/devices/power_manager_types.hpp"
// fdcan

namespace {

gn10_can::devices::power_manager::Config config{false, 1000};

FDCANDriver fdcan_driver(&hfdcan1);
gn10_can::FDCANBus fdcan_bus(fdcan_driver);
gn10_can::devices::PowerManagerServer server(fdcan_bus, 1);

adc_monitor::adc analog(&hadc1);

// float voltage_data_ch[4] = {0};

constexpr uint32_t heartbeat_toggle_interval_ms = 200;

void update_heartbeat_led()
{
    static uint32_t last_time = 0;
    if ((HAL_GetTick() - last_time) >= heartbeat_toggle_interval_ms) {
        last_time = HAL_GetTick();
        HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
    }
}

void update_sensor()
{
    static uint32_t last_tick = 0;
    if ((HAL_GetTick() - last_tick) >= config.sensor_rate_ms) {
        last_tick = HAL_GetTick();
        gn10_can::devices::power_manager::Sensor sensor_msg[4];
        /*4ch分の電圧を取得*/
        for (uint8_t i = 0; i < 4; i++) {
            /*電圧を取得してCANで送信*/
            sensor_msg[i].voltage = analog.Read_Polling(static_cast<adc_monitor::channel>(i + 1));
            sensor_msg[i].current = i + 1;
            server.set_sensor(sensor_msg[i]);
        }
    }
}

}  // namespace

void setup()
{
    analog.init();
    fdcan_driver.init();
}

void loop()
{
    if (server.get_new_init(config)) {
        HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
    }

    if (analog.Read_Polling(adc_monitor::channel::CH_4) >= 1.0f) {
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    }

    update_heartbeat_led();
    update_sensor();
}

extern "C" {
// C言語側の関数のオーバーライド
/**
 * @brief Receive callback for FDCAN FIFO0.
 */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo0ITs)
{
    fdcan_bus.update();
}
}
