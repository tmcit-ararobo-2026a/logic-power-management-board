
#pragma once

#include "adc.h"

namespace adc_monitor {

#define ADC_CH_NUM 4

enum class channel : uint8_t;

class adc
{
private:
    ADC_HandleTypeDef* hadc_;

    uint32_t sampling[ADC_CH_NUM];

public:
    adc(ADC_HandleTypeDef* _hadc) : hadc_(_hadc) {};

    void init();

    uint32_t AnalogRead(channel ch_);
};

enum class channel : uint8_t {
    CH_1,
    CH_2,
    CH_3,
    CH_4,
    CH_5,
    CH_6,
    CH_7,
    CH_8,
    CH_9,
    CH_10,
    CH_11,
    CH_12,
    CH_13,
    CH_14,
    CH_15,
    CH_16,
    CH_17,
    CH_18,
};

}  // namespace adc_monitor
