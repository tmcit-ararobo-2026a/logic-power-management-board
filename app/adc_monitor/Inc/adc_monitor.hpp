
#pragma once

#include "adc.h"

namespace adc_monitor {

#define ADC_CH_NUM 4

enum class channel : uint8_t;
enum class mode : uint8_t;
class adc
{
private:
    struct adc_monitor_buffer_TypeDef {
        HAL_StatusTypeDef HAL_ADCEx_Calibration_Start;
        uint32_t HAL_ADCEx_Calibration_GetValue;
    };

    adc_monitor_buffer_TypeDef adc_monitor_;

    ADC_HandleTypeDef* hadc_;

    uint32_t sampling[ADC_CH_NUM];

    ADC_ChannelConfTypeDef adc_ch_conf;
    ADC_InjectionConfTypeDef adc_injection_ch_conf;

    uint32_t channel_(channel ch_);

public:
    adc(ADC_HandleTypeDef* _hadc) : hadc_(_hadc) {};

    void init();

    float Read_Polling(channel ch_);
    float Read_IT(channel ch_);
    float Read_DMA(channel ch_);

    float Read_fast_Polling(channel ch_);
    float Read_fast_IT(channel ch_);
    float Read_fast_DMA(channel ch_);
};

enum class channel : uint8_t {
    CH_0,
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

enum class mode : uint8_t {
    Polling,
    IT,
    DMA,
};

enum offset_data {
    Min_Data       = 0x000,
    Max_Data_6bit  = 0x3F,
    Max_Data_8bit  = 0xFF,
    Max_Data_10bit = 0x3FF,
    Max_Data_12bit = 0xFFF,
};

}  // namespace adc_monitor
