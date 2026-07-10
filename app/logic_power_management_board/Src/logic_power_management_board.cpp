
#include "logic_power_management_board.hpp"

#include "adc.h"
#include "fdcan.h"
//

#include "adc_monitor.hpp"
#include "fdcan_driver.hpp"

adc_monitor::adc analog(&hadc1);

void setup()
{
    analog.init();

    analog.Read_Polling(adc_monitor::channel::CH_1);
}

void loop() {}
