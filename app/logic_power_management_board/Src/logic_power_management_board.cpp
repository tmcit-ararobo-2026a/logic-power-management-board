
#include "logic_power_management_board.hpp"

#include "adc.h"
#include "fdcan.h"
//

#include "adc_monitor.hpp"
#include "fdcan_driver.hpp"

adc_monitor::adc ADC(&hadc1);

void setup()
{
    ADC.init();
}

void loop() {}
