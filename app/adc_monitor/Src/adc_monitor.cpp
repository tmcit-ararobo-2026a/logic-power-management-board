
#include "adc_monitor/Inc/adc_monitor.hpp"

namespace adc_monitor {

void adc::init()
{
    adc_monitor_.HAL_ADCEx_Calibration_Start = HAL_ADCEx_Calibration_Start(hadc_, ADC_SINGLE_ENDED);

    adc_monitor_.HAL_ADCEx_Calibration_GetValue =
        HAL_ADCEx_Calibration_GetValue(hadc_, ADC_SINGLE_ENDED);
}

float adc::Read_Polling(channel ch_)
{
    HAL_ADC_Stop(hadc_);

    adc_ch_conf.Channel          = channel_(ch_);
    adc_ch_conf.Rank             = ADC_REGULAR_RANK_1;
    adc_ch_conf.SamplingTime     = ADC_SAMPLETIME_12CYCLES_5;
    adc_ch_conf.SingleDiff       = ADC_SINGLE_ENDED;
    adc_ch_conf.OffsetNumber     = ADC_OFFSET_NONE;
    adc_ch_conf.Offset           = offset_data::Max_Data_12bit;
    adc_ch_conf.OffsetSign       = ADC_OFFSET_SIGN_POSITIVE;
    adc_ch_conf.OffsetSaturation = FunctionalState::DISABLE;

    HAL_ADC_ConfigChannel(hadc_, &adc_ch_conf);

    HAL_ADC_Start(hadc_);

    if (!HAL_ADC_PollForConversion(hadc_, 1)) {
        return 3.3f * (float)HAL_ADC_GetValue(hadc_) / 4095.0f;
    }

    return 0.0f;
}

float adc::Read_IT(channel ch_)
{
    return 0.0f;
}

float adc::Read_DMA(channel ch_)
{
    return 0.0f;
}

float adc::Read_fast_Polling(channel ch_)
{
    HAL_ADCEx_InjectedStop(hadc_);

    HAL_ADCEx_InjectedConfigChannel(hadc_, &adc_injection_ch_conf);

    HAL_ADCEx_InjectedStart(hadc_);

    if (HAL_ADCEx_InjectedPollForConversion(hadc_, 1)) {
        return 3.3f * (float)HAL_ADCEx_InjectedGetValue(hadc_, ADC_INJECTED_RANK_1) / 4095.0f;
    }

    return 0.0f;
}

float adc::Read_fast_IT(channel ch_)
{
    return 0.0f;
}

float adc::Read_fast_DMA(channel ch_)
{
    return 0.0f;
}

uint32_t adc::channel_(channel ch_)
{
    switch (ch_) {
        case channel::CH_0:
            return ADC_CHANNEL_1;
            break;

        case channel::CH_1:
            return ADC_CHANNEL_1;
            break;

        case channel::CH_2:
            return ADC_CHANNEL_2;
            break;

        case channel::CH_3:
            return ADC_CHANNEL_3;
            break;

        case channel::CH_4:
            return ADC_CHANNEL_4;
            break;

        case channel::CH_5:
            return ADC_CHANNEL_5;
            break;

        case channel::CH_6:
            return ADC_CHANNEL_6;
            break;

        case channel::CH_7:
            return ADC_CHANNEL_7;
            break;

        case channel::CH_8:
            return ADC_CHANNEL_8;
            break;

        case channel::CH_9:
            return ADC_CHANNEL_9;
            break;

        case channel::CH_10:
            return ADC_CHANNEL_10;
            break;

        case channel::CH_11:
            return ADC_CHANNEL_11;
            break;

        case channel::CH_12:
            return ADC_CHANNEL_12;
            break;

        case channel::CH_13:
            return ADC_CHANNEL_13;
            break;

        case channel::CH_14:
            return ADC_CHANNEL_14;
            break;

        case channel::CH_15:
            return ADC_CHANNEL_15;
            break;

        case channel::CH_16:
            return ADC_CHANNEL_16;
            break;

        case channel::CH_17:
            return ADC_CHANNEL_17;
            break;

        case channel::CH_18:
            return ADC_CHANNEL_18;
            break;
    }

    return ADC_CHANNEL_1;
}

}  // namespace adc_monitor