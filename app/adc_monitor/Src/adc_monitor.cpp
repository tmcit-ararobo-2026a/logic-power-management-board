
#include "adc_monitor.hpp"

namespace adc_monitor {

void adc::init()
{
    // HAL_ADC_Start_IT(hadc_);
    HAL_ADC_Start_DMA(hadc_, sampling, ADC_CH_NUM);
}

uint32_t adc::AnalogRead(channel ch_) {}

}  // namespace adc_monitor